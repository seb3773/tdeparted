/* Copyright (C) 2004 Bart
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "GParted_Core.h"
#include "Win_GParted_TQt.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glibmm/thread.h>
#include <glibmm/ustring.h>
#include <iostream>
#include <stdlib.h>
#include <tdeaboutdata.h>
#include <tdeapplication.h>
#include <tdecmdlineargs.h>
#include <tqmessagebox.h>
#include <tqwidget.h>

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>


int main( int argc, char *argv[] )
{
	GParted::GParted_Core::mainthread = Glib::Thread::self();

	TDEAboutData about(
		"tdeparted",
		"tdeparted",
		"tdeParted",
		PACKAGE_VERSION,
		(int)TDEAboutData::License_GPL
	);
	TDECmdLineArgs::init( argc, argv, &about );
	TDEApplication app;

	// Single instance guard
	int guard_fd = socket( AF_UNIX, SOCK_STREAM, 0 );
	if (guard_fd >= 0)
	{
		(void)fcntl( guard_fd, F_SETFD, FD_CLOEXEC );

		sockaddr_un addr;
		memset( &addr, 0, sizeof(addr) );
		addr.sun_family = AF_UNIX;
		addr.sun_path[0] = '\0';
		strncpy( addr.sun_path + 1, "tdeparted.single_instance", sizeof(addr.sun_path) - 2 );
		const socklen_t addrlen = (socklen_t)( offsetof(sockaddr_un, sun_path) + 1 + strlen( addr.sun_path + 1 ) );

		if (bind( guard_fd, (const struct sockaddr*)&addr, addrlen ) != 0)
		{
			if (errno == EADDRINUSE)
			{
				TQMessageBox::critical(
					0,
					TQString::fromLatin1("Error"),
					TQString::fromLatin1("Error: tdeparted already running"),
					TQMessageBox::Ok,
					TQMessageBox::NoButton,
					TQMessageBox::NoButton
				);
				return 1;
			}
			close( guard_fd );
		}
	}

	std::cout << GParted::GParted_Core::get_version_and_config_string() << std::endl;

	if ( getuid() != 0 )
	{
		const Glib::ustring error_msg(_("Root privileges are required for running tdeParted"));
		std::cerr << error_msg << std::endl;

		TQMessageBox::critical(
			0,
			TQString::fromLatin1("tdeParted"),
			TQString::fromUtf8(error_msg.c_str()),
			TQMessageBox::Ok,
			TQMessageBox::NoButton,
			TQMessageBox::NoButton
		);
		exit(EXIT_FAILURE);
	}

	// Collect user-specified device paths, filtering out any TDE/Qt arguments
	// that were not consumed by TDECmdLineArgs::init() (e.g. --style, --display).
	std::vector<Glib::ustring> user_devices;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			continue;  // Skip options and their values
		user_devices.push_back( Glib::ustring( argv[i] ) );
	}

	GParted::Win_GParted_TQt win_gparted( user_devices );
	app.setMainWidget( &win_gparted );
	win_gparted.show();

	return app.exec();
}
