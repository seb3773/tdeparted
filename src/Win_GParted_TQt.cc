/* Copyright (C) 2026
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

#include "Win_GParted_TQt.h"
#include "SupportedFileSystems.h"
#include "Mount_Info.h"
#include "Utils.h"
#include "OperationCreate.h"
#include "OperationCopy.h"
#include "OperationDelete.h"
#include "OperationChangeUUID.h"
#include "OperationCheck.h"
#include "OperationFormat.h"
#include "OperationLabelFileSystem.h"
#include "OperationNamePartition.h"
#include "OperationResizeMove.h"
#include "PartitionLUKS.h"
#include "Mount_Info.h"
#include "Proc_Partitions_Info.h"
#include "PasswordRAMStore.h"
#include "OperationDetail.h"

#include <tdeglobal.h>
#include <kiconloader.h>
#include <tqapplication.h>
#include <tqbitmap.h>
#include <tqfontmetrics.h>
#include <tqheader.h>
#include <tqimage.h>
#include <tqmessagebox.h>
#include <tqiconset.h>
#include <tqmime.h>
#include <tqgroupbox.h>
#include <tqstringlist.h>
#include <tqcolor.h>
#include <tqcombobox.h>
#include <tqpainter.h>
#include <tqpen.h>
#include <tqfontmetrics.h>
#include <tqevent.h>
#include <tqlayout.h>
#include <tqlabel.h>
#include <tqmenubar.h>
#include <tqstring.h>
#include <tqstatusbar.h>
#include <tqsplitter.h>
#include <tqtoolbutton.h>
#include <tqtoolbar.h>
#include <tqstring.h>
#include <tqiconset.h>
#include <tqmime.h>
#include <tqstringlist.h>
#include <tqcursor.h>
#include <tqdialog.h>
#include <tqscrollview.h>
#include <tqpushbutton.h>
#include <tqspinbox.h>
#include <tqpainter.h>
#include <tqlineedit.h>
#include <tqcheckbox.h>
#include <tqprogressbar.h>
#include <tqfiledialog.h>
#include <tqtimer.h>
#include <tqvalidator.h>
#include <tqregexp.h>
#include <tqclipboard.h>
#include <tqtextedit.h>
#include <kurlrequester.h>
#include <kurl.h>
#include <tdefile.h>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstring>

#include <fcntl.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>

#include <glib.h>
#include <glibmm/shell.h>
#include <glibmm/miscutils.h>
#include <glibmm/main.h>

#include <map>
#include <fstream>

namespace GParted
{

#include "tdeparted_icon_png.inc"
#include "tdeparted_about_png.inc"
#include "ssd_drive2_png.inc"
#include "nvme_drive2_png.inc"
#include "usb_drive2_png.inc"
#include "hard_drive2_png.inc"
#include "mount_png.inc"
#include "unmount_png.inc"
#include "new_png.inc"
#include "info_png.inc"
#include "pending_png.inc"
#include "resize_png.inc"
#include "sec_erase_png.inc"
#include "file_system_png.inc"
#include "flag_png.inc"
#include "label_png.inc"
#include "name_png.inc"
#include "delete_png.inc"
#include "bench_png.inc"
#include "quit_png.inc"
#include "smart_png.inc"
#include "device_png.inc"

static const char *const APP_BRAND_NAME = "tdeParted";

static TQPixmap load_icon_by_name( const char *name );

static TQPixmap load_embedded_png_pixmap( const unsigned char *data, unsigned int len );

static TQPixmap load_embedded_ui_icon_by_name_tqt( const char *name )
{
	if (!name || !name[0])
		return TQPixmap();
	if (!strcmp( name, "new" ))
		return load_embedded_png_pixmap( ___new_png, (unsigned int)___new_png_len );
	if (!strcmp( name, "delete" ))
		return load_embedded_png_pixmap( ___delete_png, (unsigned int)___delete_png_len );
	if (!strcmp( name, "file_system" ))
		return load_embedded_png_pixmap( ___file_system_png, (unsigned int)___file_system_png_len );
	if (!strcmp( name, "info" ))
		return load_embedded_png_pixmap( ___info_png, (unsigned int)___info_png_len );
	if (!strcmp( name, "pending" ))
		return load_embedded_png_pixmap( ___pending_png, (unsigned int)___pending_png_len );
	if (!strcmp( name, "resize" ))
		return load_embedded_png_pixmap( ___resize_png, (unsigned int)___resize_png_len );
	if (!strcmp( name, "sec_erase" ))
		return load_embedded_png_pixmap( ___sec_erase_png, (unsigned int)___sec_erase_png_len );
	if (!strcmp( name, "flag" ))
		return load_embedded_png_pixmap( ___flag_png, (unsigned int)___flag_png_len );
	if (!strcmp( name, "label" ))
		return load_embedded_png_pixmap( ___label_png, (unsigned int)___label_png_len );
	if (!strcmp( name, "name" ))
		return load_embedded_png_pixmap( ___name_png, (unsigned int)___name_png_len );
	if (!strcmp( name, "bench" ))
		return load_embedded_png_pixmap( ___bench_png, (unsigned int)___bench_png_len );
	if (!strcmp( name, "quit" ))
		return load_embedded_png_pixmap( ___quit_png, (unsigned int)___quit_png_len );
	if (!strcmp( name, "smart" ))
		return load_embedded_png_pixmap( ___smart_png, (unsigned int)___smart_png_len );
	if (!strcmp( name, "device" ))
		return load_embedded_png_pixmap( ___device_png, (unsigned int)___device_png_len );
	return TQPixmap();
}

static int pick_benchmark_mountpoint_tqt( const Device &d, uint64_t need_bytes, Glib::ustring &mountpoint );
static TQString format_mbs_tqt( double mbs );
static int simple_benchmark_seq1m_tqt( const Glib::ustring &mountpoint,
	                                  uint64_t total_bytes,
	                                  uint32_t block_size,
	                                  TQProgressBar *pb,
	                                  TQLabel *phase,
	                                  double &out_write_mbs,
	                                  double &out_read_mbs,
	                                  TQString &out_error );

static TQPixmap load_embedded_png_pixmap( const unsigned char *data, unsigned int len )
{
	TQImage img;
	if (!img.loadFromData( (const uchar*)data, (int)len, "PNG" ))
		return TQPixmap();
	TQPixmap pm;
	pm.convertFromImage( img );
	return pm;
}

void Win_GParted_TQt::menu_device_simple_benchmark()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	const Device &d = m_devices[m_current_device];
	const Glib::ustring dev_path = d.get_path();
	const uint32_t block = 1024U * 1024U;
	const uint64_t total = 1024ULL * 1024ULL * 1024ULL;

	Glib::ustring mountpoint;
	if (!pick_benchmark_mountpoint_tqt( d, total + (64ULL << 20), mountpoint ))
	{
		TQMessageBox::critical( this, tr("Quick Benchmark"), tr("No mounted partition with enough free space was found on this device."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	TQDialog dlg( this, 0, true );
	dlg.setCaption( tr("Quick Benchmark") );
	TQVBoxLayout *v = new TQVBoxLayout( &dlg );
	v->setMargin( 8 );
	v->setSpacing( 6 );

	TQString title = tr("Device:") + TQString::fromLatin1(" ") + TQString::fromUtf8( dev_path.c_str() );
	TQLabel *lbl_title = new TQLabel( title, &dlg );
	TQFont tf = lbl_title->font();
	tf.setBold( true );
	lbl_title->setFont( tf );
	v->addWidget( lbl_title );

	TQString mp = TQString::fromUtf8( mountpoint.c_str() );
	TQLabel *lbl_mp = new TQLabel( mp, &dlg );
	v->addWidget( lbl_mp );

	TQLabel *lbl_bench = new TQLabel( tr("Benchmark: SEQ1MQ8T1"), &dlg );
	v->addWidget( lbl_bench );

	TQFrame *sep = new TQFrame( &dlg );
	sep->setFrameShape( TQFrame::HLine );
	sep->setFrameShadow( TQFrame::Sunken );
	v->addWidget( sep );

	TQLabel *lbl_phase = new TQLabel( tr("Preparing"), &dlg );
	v->addWidget( lbl_phase );
	TQProgressBar *pb = new TQProgressBar( &dlg );
	pb->setCenterIndicator( true );
	v->addWidget( pb );

	TQWidget *result_container = new TQWidget( &dlg );
	TQGridLayout *g = new TQGridLayout( result_container, 2, 2, 0, 6 );
	TQLabel *lbl_read = new TQLabel( tr("Read:"), result_container );
	TQLabel *lbl_write = new TQLabel( tr("Write:"), result_container );
	TQLabel *val_read = new TQLabel( TQString(), result_container );
	TQLabel *val_write = new TQLabel( TQString(), result_container );
	TQFont bf = val_read->font();
	bf.setBold( true );
	val_read->setFont( bf );
	val_write->setFont( bf );
	g->addWidget( lbl_read, 0, 0 );
	g->addWidget( val_read, 0, 1 );
	g->addWidget( lbl_write, 1, 0 );
	g->addWidget( val_write, 1, 1 );
	result_container->hide();
	v->addWidget( result_container, 1 );

	TQHBoxLayout *hb = new TQHBoxLayout();
	hb->addStretch( 1 );
	TQPushButton *btn_close = new TQPushButton( tr("Close"), &dlg );
	hb->addWidget( btn_close );
	v->addLayout( hb );
	TQObject::connect( btn_close, TQT_SIGNAL(clicked()), &dlg, TQT_SLOT(accept()) );
	btn_close->setEnabled( false );

	dlg.resize( 520, 280 );
	dlg.show();
	tqApp->processEvents();

	double write_mbs = 0.0;
	double read_mbs = 0.0;
	TQString err;

	int ok = simple_benchmark_seq1m_tqt( mountpoint, total, block, pb, lbl_phase, write_mbs, read_mbs, err );
	if (!ok)
	{
		dlg.hide();
		TQMessageBox::critical( this, tr("Quick Benchmark"), tr("Error") + TQString::fromLatin1(": ") + err, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	pb->hide();
	lbl_phase->hide();
	val_read->setText( format_mbs_tqt( read_mbs ) );
	val_write->setText( format_mbs_tqt( write_mbs ) );
	result_container->show();
	btn_close->setEnabled( true );
	tqApp->processEvents();

	dlg.exec();
}

static const TQPixmap &mount_icon_pixmap_tqt( bool mounted )
{
	static TQPixmap pm_mount;
	static TQPixmap pm_unmount;
	static int init = 0;
	if (!init)
	{
		init = 1;
		pm_mount = load_embedded_png_pixmap( ___mount_png, (unsigned int)___mount_png_len );
		pm_unmount = load_embedded_png_pixmap( ___unmount_png, (unsigned int)___unmount_png_len );
	}
	return mounted ? pm_unmount : pm_mount;
}

static TQPixmap make_disabled_pixmap_tqt( const TQPixmap &pm )
{
	if (pm.isNull())
		return TQPixmap();
	TQImage img = pm.convertToImage();
	if (img.isNull())
		return TQPixmap();
	img = img.convertDepth( 32 );
	const int w = img.width();
	const int h = img.height();
	for (int y = 0; y < h; y++)
	{
		unsigned int *row = (unsigned int*)img.scanLine( y );
		for (int x = 0; x < w; x++)
		{
			const unsigned int p = row[x];
			const unsigned int a = (p >> 24) & 0xffU;
			const unsigned int r = (p >> 16) & 0xffU;
			const unsigned int g = (p >> 8) & 0xffU;
			const unsigned int b = p & 0xffU;
			unsigned int gray = (r * 30U + g * 59U + b * 11U) / 100U;
			gray = (gray * 65U) / 100U + 96U;
			if (gray > 255U)
				gray = 255U;
			row[x] = (a << 24) | (gray << 16) | (gray << 8) | gray;
		}
	}
	TQPixmap out;
	out.convertFromImage( img );
	return out;
}

static void set_toolbar_button_iconset_tqt( TDEToolBarButton *btn, const TQPixmap &pm )
{
	if (!btn)
		return;
	if (pm.isNull())
		return;

	TQIconSet is;
	is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Normal );
	is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Active );
	is.setPixmap( make_disabled_pixmap_tqt( pm ), TQIconSet::Automatic, TQIconSet::Disabled );
	btn->setIconSet( is );
}

enum DeviceType_TQt
{
	DEVTYPE_UNKNOWN = 0,
	DEVTYPE_USB_STORAGE,
	DEVTYPE_NVME_SSD,
	DEVTYPE_SATA_SSD,
	DEVTYPE_MECHANICAL
};

static const TQPixmap &device_type_icon_pixmap_tqt( DeviceType_TQt t )
{
	static TQPixmap pm_ssd;
	static TQPixmap pm_nvme;
	static TQPixmap pm_usb;
	static TQPixmap pm_hdd;
	static int init = 0;
	if (!init)
	{
		init = 1;
		pm_ssd  = load_embedded_png_pixmap( ___ssd_drive2_png, (unsigned int)___ssd_drive2_png_len );
		pm_nvme = load_embedded_png_pixmap( ___nvme_drive2_png, (unsigned int)___nvme_drive2_png_len );
		pm_usb  = load_embedded_png_pixmap( ___usb_drive2_png, (unsigned int)___usb_drive2_png_len );
		pm_hdd  = load_embedded_png_pixmap( ___hard_drive2_png, (unsigned int)___hard_drive2_png_len );
	}

	switch (t)
	{
		case DEVTYPE_USB_STORAGE: return pm_usb;
		case DEVTYPE_NVME_SSD:    return pm_nvme;
		case DEVTYPE_SATA_SSD:    return pm_ssd;
		case DEVTYPE_MECHANICAL:  return pm_hdd;
		case DEVTYPE_UNKNOWN:
		default: break;
	}
	return pm_hdd;
}

static const TQPixmap &tdeparted_app_icon_pixmap()
{
	static TQPixmap pm;
	static int init = 0;
	if (!init)
	{
		init = 1;
		pm = load_embedded_png_pixmap( tdeparted_icon_png, (unsigned int)sizeof(tdeparted_icon_png) );
	}
	return pm;
}

static const TQPixmap &tdeparted_about_pixmap()
{
	static TQPixmap pm;
	static int init = 0;
	if (!init)
	{
		init = 1;
		pm = load_embedded_png_pixmap( tdeparted_about_png, (unsigned int)sizeof(tdeparted_about_png) );
	}
	return pm;
}

static TQString strip_gtk_mnemonic_underscores( const TQString &in )
{
	TQString out;
	out.reserve( in.length() );
	for (int i = 0; i < (int)in.length(); i++)
	{
		const TQChar c = in[i];
		if (c != '_')
		{
			out += c;
			continue;
		}
		if (i + 1 < (int)in.length() && in[i + 1] == '_')
		{
			out += TQChar('_');
			i++;
			continue;
		}
	}
	return out;
}

static uint64_t imaging_now_nsec()
{
	struct timespec ts;
	if (clock_gettime( CLOCK_MONOTONIC_RAW, &ts ) != 0)
		return 0;
	return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static uint64_t imaging_file_size_u64( const Glib::ustring &path )
{
	struct stat st;
	if (stat( path.c_str(), &st ) != 0)
		return 0;
	if (S_ISBLK( st.st_mode ))
	{
		uint64_t sz = 0;
		const int fd = open( path.c_str(), O_RDONLY );
		if (fd >= 0)
		{
			if (ioctl( fd, BLKGETSIZE64, &sz ) != 0)
				sz = 0;
			close( fd );
		}
		return sz;
	}
	if (st.st_size < 0)
		return 0;
	return (uint64_t)st.st_size;
}

static size_t imaging_blksszget_align( int fd )
{
	int ssz = 0;
	if (fd < 0)
		return 0;
	if (ioctl( fd, BLKSSZGET, &ssz ) != 0)
		return 0;
	if (ssz <= 0)
		return 0;
	const size_t a = (size_t)ssz;
	if ((a & (a - 1u)) != 0u)
		return 0;
	if (a < 512u)
		return 0;
	return a;
}

static Glib::ustring imaging_errno_context( const Glib::ustring &prefix )
{
	const int e = errno;
	Glib::ustring s = prefix;
	s += ": ";
	s += Glib::ustring( strerror( e ) );
	return s;
}

ImagingWorker_TQt::ImagingWorker_TQt( const Glib::ustring &src_path,
	                                  const Glib::ustring &dst_path,
	                                  uint64_t bytes_total,
	                                  int src_is_blockdev,
	                                  int dst_is_blockdev,
	                                  int direction_restore,
	                                  int opt_rescue_zerofill,
	                                  int opt_sparse_zeros,
	                                  int opt_sha256,
	                                  int opt_sha256_verify )
	: m_src_path( src_path ),
	  m_dst_path( dst_path ),
	  m_bytes_total( bytes_total ),
	  m_src_is_blockdev( src_is_blockdev ),
	  m_dst_is_blockdev( dst_is_blockdev ),
	  m_direction_restore( direction_restore ),
	  m_opt_rescue_zerofill( opt_rescue_zerofill ),
	  m_opt_sparse_zeros( opt_sparse_zeros ),
	  m_opt_sha256( opt_sha256 ),
	  m_opt_sha256_verify( opt_sha256_verify ),
	  m_cancel_requested( 0 ),
	  m_success( 0 ),
	  m_cancelled( 0 ),
	  m_fd_src( -1 ),
	  m_fd_dst( -1 ),
	  m_fd_src_buf( -1 ),
	  m_fd_dst_buf( -1 )
{
}

void ImagingWorker_TQt::cancel()
{
	m_state_mutex.lock();
	m_cancel_requested = 1;
	m_state_mutex.unlock();
}

bool ImagingWorker_TQt::get_success()
{
	m_state_mutex.lock();
	const int v = m_success;
	m_state_mutex.unlock();
	return v ? true : false;
}

bool ImagingWorker_TQt::get_cancelled()
{
	m_state_mutex.lock();
	const int v = m_cancelled;
	m_state_mutex.unlock();
	return v ? true : false;
}

void ImagingWorker_TQt::get_updates( std::vector<ImagingUpdate_TQt> &updates )
{
	m_queue_mutex.lock();
	updates = m_update_queue;
	m_update_queue.clear();
	m_queue_mutex.unlock();
}

void ImagingWorker_TQt::run()
{
	m_state_mutex.lock();
	m_cancel_requested = 0;
	m_success = 0;
	m_cancelled = 0;
	m_fd_src = -1;
	m_fd_dst = -1;
	m_fd_src_buf = -1;
	m_fd_dst_buf = -1;
	m_state_mutex.unlock();

	const int src_flags = (m_src_is_blockdev ? O_DIRECT : 0) | O_RDONLY;
	int dst_flags = (m_dst_is_blockdev ? O_DIRECT : 0) | O_WRONLY;
	if (!m_dst_is_blockdev)
		dst_flags |= O_CREAT | O_TRUNC;

	GChecksum *sum = 0;
	GChecksum *sum_verify = 0;

	m_fd_src = open( m_src_path.c_str(), src_flags );
	if (m_fd_src < 0)
	{
		ImagingUpdate_TQt upd;
		upd.bytes_done = 0;
		upd.bytes_total = m_bytes_total;
		upd.seconds_elapsed = 0.0;
		upd.error_code = errno;
		upd.error_context = imaging_errno_context( "open source" );
		m_queue_mutex.lock();
		m_update_queue.push_back( upd );
		m_queue_mutex.unlock();
		return;
	}
	m_fd_dst = open( m_dst_path.c_str(), dst_flags, 0644 );
	if (m_fd_dst < 0)
	{
		ImagingUpdate_TQt upd;
		upd.bytes_done = 0;
		upd.bytes_total = m_bytes_total;
		upd.seconds_elapsed = 0.0;
		upd.error_code = errno;
		upd.error_context = imaging_errno_context( "open destination" );
		m_queue_mutex.lock();
		m_update_queue.push_back( upd );
		m_queue_mutex.unlock();
		close( m_fd_src );
		m_fd_src = -1;
		return;
	}

	size_t align = 512u;
	if (m_src_is_blockdev)
	{
		const size_t a = imaging_blksszget_align( m_fd_src );
		if (a > align)
			align = a;
	}
	if (m_dst_is_blockdev)
	{
		const size_t a = imaging_blksszget_align( m_fd_dst );
		if (a > align)
			align = a;
	}
	const size_t buf_size = (size_t)(4u * 1024u * 1024u);
	void *buf = 0;
	if (posix_memalign( &buf, align, buf_size ) != 0 || !buf)
	{
		ImagingUpdate_TQt upd;
		upd.bytes_done = 0;
		upd.bytes_total = m_bytes_total;
		upd.seconds_elapsed = 0.0;
		upd.error_code = ENOMEM;
		upd.error_context = "posix_memalign";
		m_queue_mutex.lock();
		m_update_queue.push_back( upd );
		m_queue_mutex.unlock();
		close( m_fd_src );
		close( m_fd_dst );
		m_fd_src = -1;
		m_fd_dst = -1;
		return;
	}

	if (m_src_is_blockdev)
		m_fd_src_buf = open( m_src_path.c_str(), O_RDONLY );
	if (m_dst_is_blockdev)
		m_fd_dst_buf = open( m_dst_path.c_str(), O_WRONLY );
	if (m_opt_sha256)
		sum = g_checksum_new( G_CHECKSUM_SHA256 );

	uint64_t bytes_done = 0;
	const uint64_t t0 = imaging_now_nsec();
	uint64_t last_emit = t0;

	while (bytes_done < m_bytes_total)
	{
		m_state_mutex.lock();
		const int cancel_now = m_cancel_requested;
		m_state_mutex.unlock();
		if (cancel_now)
		{
			m_state_mutex.lock();
			m_cancelled = 1;
			m_success = 0;
			m_state_mutex.unlock();
			break;
		}

		size_t want = buf_size;
		const uint64_t remaining = m_bytes_total - bytes_done;
		if ((uint64_t)want > remaining)
			want = (size_t)remaining;
		const int need_direct = (m_src_is_blockdev || m_dst_is_blockdev) ? 1 : 0;
		const int need_buf_tail = (need_direct && ((remaining & (align - 1u)) != 0u)) ? 1 : 0;
		if (need_direct && !need_buf_tail)
			want &= ~(align - 1u);
		if (want == 0)
			want = (size_t)remaining;

		const int use_buf = (need_buf_tail && (remaining == (uint64_t)want)) ? 1 : 0;
		const int fd_r = (use_buf && m_fd_src_buf >= 0) ? m_fd_src_buf : m_fd_src;
		const int fd_w = (use_buf && m_fd_dst_buf >= 0) ? m_fd_dst_buf : m_fd_dst;

		size_t want2 = want;
		ssize_t rd = read( fd_r, buf, want2 );
		if (rd < 0)
		{
			m_state_mutex.lock();
			const int cancel_now_rd = m_cancel_requested;
			m_state_mutex.unlock();
			if (cancel_now_rd && (errno == EBADF || errno == EINTR))
			{
				m_state_mutex.lock();
				m_cancelled = 1;
				m_success = 0;
				m_state_mutex.unlock();
				break;
			}
			if (m_opt_rescue_zerofill)
			{
				ImagingUpdate_TQt upd;
				upd.bytes_done = bytes_done;
				upd.bytes_total = m_bytes_total;
				upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
				upd.error_code = errno;
				upd.error_context = imaging_errno_context( "read (rescue: zero-filled)" );
				m_queue_mutex.lock();
				m_update_queue.push_back( upd );
				m_queue_mutex.unlock();

				memset( buf, 0, want2 );
				rd = (want2 <= (size_t)SSIZE_MAX) ? (ssize_t)want2 : (ssize_t)SSIZE_MAX;
				(void)lseek( fd_r, (off_t)want2, SEEK_CUR );
			}
			else
			{
				ImagingUpdate_TQt upd;
				upd.bytes_done = bytes_done;
				upd.bytes_total = m_bytes_total;
				upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
				upd.error_code = errno;
				upd.error_context = imaging_errno_context( "read" );
				m_queue_mutex.lock();
				m_update_queue.push_back( upd );
				m_queue_mutex.unlock();
				break;
			}
		}
		if (rd == 0)
			break;

		const size_t rd_sz = (size_t)rd;
		if (sum)
		{
			g_checksum_update( sum, (const guchar *)buf, rd_sz );
		}

		if (m_opt_sparse_zeros && sum && !m_dst_is_blockdev)
		{
			const unsigned char *p = (const unsigned char *)buf;
			size_t k = 0;
			for (; k < rd_sz; k++)
			{
				if (__builtin_expect( p[k] != 0, 0 ))
					break;
			}
			if (k == rd_sz)
			{
				if (lseek( m_fd_dst, (off_t)rd_sz, SEEK_CUR ) < 0)
				{
					ImagingUpdate_TQt upd;
					upd.bytes_done = bytes_done;
					upd.bytes_total = m_bytes_total;
					upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
					upd.error_code = errno;
					upd.error_context = imaging_errno_context( "lseek (sparse)" );
					m_queue_mutex.lock();
					m_update_queue.push_back( upd );
					m_queue_mutex.unlock();
					break;
				}

				bytes_done += (uint64_t)rd_sz;

				const uint64_t now2 = imaging_now_nsec();
				if (now2 - last_emit >= 200000000ull || bytes_done >= m_bytes_total)
				{
					ImagingUpdate_TQt upd;
					upd.bytes_done = bytes_done;
					upd.bytes_total = m_bytes_total;
					upd.seconds_elapsed = (double)(now2 - t0) / 1000000000.0;
					upd.error_code = 0;
					upd.error_context.clear();
					m_queue_mutex.lock();
					m_update_queue.push_back( upd );
					m_queue_mutex.unlock();
					last_emit = now2;
				}
				continue;
			}
		}

		size_t off = 0;
		while (off < (size_t)rd)
		{
			m_state_mutex.lock();
			const int cancel_now2 = m_cancel_requested;
			m_state_mutex.unlock();
			if (cancel_now2)
			{
				m_state_mutex.lock();
				m_cancelled = 1;
				m_success = 0;
				m_state_mutex.unlock();
				off = (size_t)rd;
				break;
			}

			ssize_t wr = write( fd_w, (const char *)buf + off, (size_t)rd - off );
			if (wr < 0)
			{
				m_state_mutex.lock();
				const int cancel_now_wr = m_cancel_requested;
				m_state_mutex.unlock();
				if (cancel_now_wr && (errno == EBADF || errno == EINTR))
				{
					m_state_mutex.lock();
					m_cancelled = 1;
					m_success = 0;
					m_state_mutex.unlock();
					off = (size_t)rd;
					break;
				}
				ImagingUpdate_TQt upd;
				upd.bytes_done = bytes_done;
				upd.bytes_total = m_bytes_total;
				upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
				upd.error_code = errno;
				upd.error_context = imaging_errno_context( "write" );
				m_queue_mutex.lock();
				m_update_queue.push_back( upd );
				m_queue_mutex.unlock();
				off = (size_t)rd;
				break;
			}
			off += (size_t)wr;
		}

		bytes_done += (uint64_t)rd;

		const uint64_t now = imaging_now_nsec();
		if (now - last_emit >= 200000000ull || bytes_done >= m_bytes_total)
		{
			ImagingUpdate_TQt upd;
			upd.bytes_done = bytes_done;
			upd.bytes_total = m_bytes_total;
			upd.seconds_elapsed = (double)(now - t0) / 1000000000.0;
			upd.error_code = 0;
			upd.error_context.clear();
			m_queue_mutex.lock();
			m_update_queue.push_back( upd );
			m_queue_mutex.unlock();
			last_emit = now;
		}
	}

	free( buf );

	/* ---- Take ownership of all FDs under mutex ----
	 * This prevents cancel() from closing them under our feet.
	 * After this point, *we* are responsible for closing them. */
	m_state_mutex.lock();
	const int cancelled_now = m_cancelled;
	const int owned_fd_src     = m_fd_src;
	const int owned_fd_dst     = m_fd_dst;
	const int owned_fd_src_buf = m_fd_src_buf;
	const int owned_fd_dst_buf = m_fd_dst_buf;
	m_fd_src     = -1;
	m_fd_dst     = -1;
	m_fd_src_buf = -1;
	m_fd_dst_buf = -1;
	if (!m_cancelled)
		m_success = (bytes_done >= m_bytes_total) ? 1 : 0;
	m_state_mutex.unlock();

	/* ---- Truncate regular file to exact image size ---- */
	if (!cancelled_now && !m_dst_is_blockdev && owned_fd_dst >= 0)
	{
		if (ftruncate( owned_fd_dst, (off_t)m_bytes_total ) != 0)
		{
			ImagingUpdate_TQt upd;
			upd.bytes_done = bytes_done;
			upd.bytes_total = m_bytes_total;
			upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
			upd.error_code = errno;
			upd.error_context = imaging_errno_context( "ftruncate" );
			m_queue_mutex.lock();
			m_update_queue.push_back( upd );
			m_queue_mutex.unlock();
			m_state_mutex.lock();
			m_success = 0;
			m_state_mutex.unlock();
		}
	}

	/* ---- Flush destination to persistent storage ---- */
	if (!cancelled_now && owned_fd_dst >= 0)
	{
		int rc = 0;
		if (m_dst_is_blockdev)
			rc = fsync( owned_fd_dst );
		else
			rc = fdatasync( owned_fd_dst );
		if (rc != 0)
		{
			ImagingUpdate_TQt upd;
			upd.bytes_done = bytes_done;
			upd.bytes_total = m_bytes_total;
			upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
			upd.error_code = errno;
			upd.error_context = imaging_errno_context( m_dst_is_blockdev ? "fsync" : "fdatasync" );
			m_queue_mutex.lock();
			m_update_queue.push_back( upd );
			m_queue_mutex.unlock();
			m_state_mutex.lock();
			m_success = 0;
			m_state_mutex.unlock();
		}
	}

	if (!cancelled_now && sum)
	{
		const gchar *hex = g_checksum_get_string( sum );
		ImagingUpdate_TQt upd;
		upd.bytes_done = bytes_done;
		upd.bytes_total = m_bytes_total;
		upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
		upd.error_code = 0;
		upd.error_context = Glib::ustring::compose( "SHA256: %1", hex ? hex : "" );
		m_queue_mutex.lock();
		m_update_queue.push_back( upd );
		m_queue_mutex.unlock();
	}

	if (!cancelled_now && sum && m_opt_sha256_verify)
	{
		sum_verify = g_checksum_new( G_CHECKSUM_SHA256 );
		if (sum_verify)
		{
			int fdv = open( m_dst_path.c_str(), O_RDONLY );
			if (fdv >= 0)
			{
				const size_t vbuf_sz = (size_t)(4u * 1024u * 1024u);
				void *vbuf = 0;
				if (posix_memalign( &vbuf, 4096u, vbuf_sz ) == 0 && vbuf)
				{
					uint64_t remain = m_bytes_total;
					while (remain > 0)
					{
						const size_t want = (remain > (uint64_t)vbuf_sz) ? vbuf_sz : (size_t)remain;
						const ssize_t n = read( fdv, vbuf, want );
						if (n <= 0)
							break;
						g_checksum_update( sum_verify, (const guchar *)vbuf, (size_t)n );
						remain -= (uint64_t)n;
					}
					free( vbuf );
				}
				close( fdv );
			}

			const gchar *hex1 = g_checksum_get_string( sum );
			const gchar *hex2 = sum_verify ? g_checksum_get_string( sum_verify ) : 0;
			if (!hex1 || !hex2 || strcmp( hex1, hex2 ) != 0)
			{
				ImagingUpdate_TQt upd;
				upd.bytes_done = bytes_done;
				upd.bytes_total = m_bytes_total;
				upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
				upd.error_code = EIO;
				upd.error_context = "SHA256 verify failed";
				m_queue_mutex.lock();
				m_update_queue.push_back( upd );
				m_queue_mutex.unlock();
				m_state_mutex.lock();
				m_success = 0;
				m_state_mutex.unlock();
			}
			else
			{
				ImagingUpdate_TQt upd;
				upd.bytes_done = bytes_done;
				upd.bytes_total = m_bytes_total;
				upd.seconds_elapsed = (double)(imaging_now_nsec() - t0) / 1000000000.0;
				upd.error_code = 0;
				upd.error_context = "SHA256 verify OK";
				m_queue_mutex.lock();
				m_update_queue.push_back( upd );
				m_queue_mutex.unlock();
			}
		}
	}

	if (sum)
		g_checksum_free( sum );
	if (sum_verify)
		g_checksum_free( sum_verify );

	/* ---- Close all owned FDs ---- */
	if (owned_fd_src_buf >= 0)
		close( owned_fd_src_buf );
	if (owned_fd_dst_buf >= 0)
		close( owned_fd_dst_buf );
	if (owned_fd_src >= 0)
		close( owned_fd_src );
	if (owned_fd_dst >= 0)
		close( owned_fd_dst );
}

struct ImagingCreateOpts_TQt
{
	TQString out_path;
	int rescue_zerofill;
	int used_space_only;
	int sha256;
	int sha256_verify;
};

struct ImagingRestoreOpts_TQt
{
	int sha256;
	int sha256_verify;
};

static bool run_imaging_create_options_dialog_tqt( TQWidget *parent, const TQString &title, const TQString &summary, const TQString &default_path, ImagingCreateOpts_TQt &out )
{
	TQDialog d( parent, 0, true );
	d.setCaption( title );
	if (!tdeparted_app_icon_pixmap().isNull())
		d.setIcon( tdeparted_app_icon_pixmap() );

	TQVBoxLayout *v = new TQVBoxLayout( &d );
	v->setMargin( 10 );
	v->setSpacing( 6 );

	TQLabel *lbl = new TQLabel( summary, &d );
	lbl->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	v->addWidget( lbl );

	TQHBoxLayout *hp = new TQHBoxLayout();
	TQLabel *lpath = new TQLabel( TQString::fromUtf8( _("Image file") ) + TQString::fromLatin1(":") , &d );
	KURLRequester *req = new KURLRequester( &d );
	req->setMode( KFile::File | KFile::LocalOnly );
	req->setURL( default_path );
	hp->addWidget( lpath );
	hp->addWidget( req, 1 );
	v->addLayout( hp );

	TQCheckBox *cb_rescue = new TQCheckBox( TQString::fromUtf8( _("Rescue (zero-fill on read errors)") ), &d );
	TQCheckBox *cb_used = new TQCheckBox( TQString::fromUtf8( _("Copy used space only") ), &d );
	TQCheckBox *cb_sha = new TQCheckBox( TQString::fromUtf8( _("Compute SHA256") ), &d );
	TQCheckBox *cb_verify = new TQCheckBox( TQString::fromUtf8( _("Verify SHA256 after write") ), &d );
	cb_rescue->setChecked( false );
	cb_used->setChecked( false );
	cb_sha->setChecked( true );
	cb_verify->setChecked( true );
	v->addWidget( cb_rescue );
	v->addWidget( cb_used );
	v->addWidget( cb_sha );
	v->addWidget( cb_verify );

	TQHBoxLayout *hb = new TQHBoxLayout();
	hb->addStretch( 1 );
	TQPushButton *ok = new TQPushButton( TQString::fromUtf8( _("OK") ), &d );
	TQPushButton *cancel = new TQPushButton( TQString::fromUtf8( _("Cancel") ), &d );
	hb->addWidget( ok );
	hb->addWidget( cancel );
	v->addLayout( hb );
	TQObject::connect( ok, TQT_SIGNAL(clicked()), &d, TQT_SLOT(accept()) );
	TQObject::connect( cancel, TQT_SIGNAL(clicked()), &d, TQT_SLOT(reject()) );

	d.resize( 720, d.sizeHint().height() );
	const int r = d.exec();
	if (r != TQDialog::Accepted)
		return false;

	out.out_path = req->url();
	out.rescue_zerofill = cb_rescue->isChecked() ? 1 : 0;
	out.used_space_only = cb_used->isChecked() ? 1 : 0;
	out.sha256 = cb_sha->isChecked() ? 1 : 0;
	out.sha256_verify = cb_verify->isChecked() ? 1 : 0;
	if (out.out_path.isEmpty())
		return false;
	if (!out.sha256)
		out.sha256_verify = 0;
	return true;
}

static bool run_imaging_restore_options_dialog_tqt( TQWidget *parent, const TQString &title, const TQString &summary, ImagingRestoreOpts_TQt &out )
{
	TQDialog d( parent, 0, true );
	d.setCaption( title );
	d.setMinimumWidth( 520 );

	TQVBoxLayout *vb = new TQVBoxLayout( &d );
	vb->setMargin( 10 );
	vb->setSpacing( 8 );

	TQLabel *l = new TQLabel( summary, &d );
	l->setTextFormat( TQt::PlainText );
	l->setAlignment( TQt::AlignLeft | TQt::AlignTop | TQt::WordBreak );
	vb->addWidget( l );

	TQCheckBox *cb_sha = new TQCheckBox( Win_GParted_TQt::tr("Compute SHA256 during restore"), &d );
	TQCheckBox *cb_verify = new TQCheckBox( Win_GParted_TQt::tr("Verify after write (slow)"), &d );
	cb_sha->setChecked( false );
	cb_verify->setChecked( false );
	cb_verify->setEnabled( false );
	TQObject::connect( cb_sha, TQT_SIGNAL(toggled(bool)), cb_verify, TQT_SLOT(setEnabled(bool)) );
	vb->addWidget( cb_sha );
	vb->addWidget( cb_verify );

	TQHBoxLayout *hb = new TQHBoxLayout();
	TQPushButton *ok = new TQPushButton( Win_GParted_TQt::tr("OK"), &d );
	TQPushButton *cancel = new TQPushButton( Win_GParted_TQt::tr("Cancel"), &d );
	hb->addStretch( 1 );
	hb->addWidget( ok );
	hb->addWidget( cancel );
	vb->addLayout( hb );
	TQObject::connect( ok, TQT_SIGNAL(clicked()), &d, TQT_SLOT(accept()) );
	TQObject::connect( cancel, TQT_SIGNAL(clicked()), &d, TQT_SLOT(reject()) );

	if (d.exec() != TQDialog::Accepted)
		return false;
	out.sha256 = cb_sha->isChecked() ? 1 : 0;
	out.sha256_verify = (out.sha256 && cb_verify->isChecked()) ? 1 : 0;
	return true;
}

enum VirtualBackend_TQt
{
	VBACKEND_NONE = 0,
	VBACKEND_LOOP = 1,
	VBACKEND_NBD  = 2
};

static bool virtual_attach_is_ro_by_ext_tqt( const Glib::ustring &img_path )
{
	if (img_path.size() < 4)
		return false;
	Glib::ustring lower;
	lower.reserve( img_path.size() );
	for (unsigned int i = 0; i < img_path.size(); i++)
		lower += (char)g_ascii_tolower( (gchar)img_path[i] );
	return (lower.rfind(".iso") == (lower.size() - 4));
}

static bool virtual_image_is_writable_tqt( const Glib::ustring &img_path )
{
	if (img_path.empty())
		return false;
	return (access( img_path.c_str(), W_OK ) == 0);
}

static bool command_exists_tqt( const char *name )
{
	Glib::ustring out;
	Glib::ustring err;
	const Glib::ustring cmd = Glib::ustring("command -v ") + name;
	return !Utils::execute_command( cmd, out, err );
}

static bool read_first_line_u64_tqt( const Glib::ustring &path, uint64_t &out )
{
	std::ifstream f( path.c_str() );
	if (!f.is_open())
		return false;
	std::string s;
	if (!std::getline( f, s ))
		return false;
	char *endp = 0;
	unsigned long long v = strtoull( s.c_str(), &endp, 10 );
	if (endp == s.c_str())
		return false;
	out = (uint64_t)v;
	return true;
}

static Glib::ustring virtual_pick_free_nbd_tqt()
{
	for (unsigned int i = 0; i < 16; i++)
	{
		char devbuf[32];
		snprintf( devbuf, sizeof(devbuf), "/dev/nbd%u", i );
		devbuf[sizeof(devbuf) - 1] = 0;
		char pidbuf[64];
		snprintf( pidbuf, sizeof(pidbuf), "/sys/block/nbd%u/pid", i );
		pidbuf[sizeof(pidbuf) - 1] = 0;
		if (access( devbuf, F_OK ) != 0)
			continue;
		if (access( pidbuf, R_OK ) != 0)
			continue;
		uint64_t pid = 0;
		if (!read_first_line_u64_tqt( pidbuf, pid ))
			continue;
		if (pid == 0)
			return Glib::ustring( devbuf );
	}
	return Glib::ustring();
}

static bool virtual_attach_loop_tqt( const Glib::ustring &img_path, bool ro, Glib::ustring &dev_out, Glib::ustring &error_msg )
{
	Glib::ustring output;
	Glib::ustring error;
	Glib::ustring cmd = "losetup --show -fP ";
	if (ro)
		cmd += "-r ";
	cmd += Glib::shell_quote( img_path );
	const bool ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
	{
		error_msg = "# " + cmd + "\n" + output + error;
		return false;
	}
	dev_out = Utils::trim_trailing_new_line( output );
	if (dev_out.empty())
	{
		error_msg = "# " + cmd + "\n" + output + error;
		return false;
	}
	return true;
}

static bool virtual_attach_nbd_tqt( const Glib::ustring &img_path, bool ro, Glib::ustring &dev_out, Glib::ustring &error_msg )
{
	if (!command_exists_tqt( "qemu-nbd" ))
	{
		error_msg = "qemu-nbd not found";
		return false;
	}
	dev_out = virtual_pick_free_nbd_tqt();
	if (dev_out.empty())
	{
		error_msg = "No free /dev/nbdX found";
		return false;
	}
	Glib::ustring output;
	Glib::ustring error;
	Glib::ustring cmd = "qemu-nbd ";
	if (ro)
		cmd += "-r ";
	cmd += "-c " + Glib::shell_quote( dev_out ) + " " + Glib::shell_quote( img_path );
	const bool ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
	{
		error_msg = "# " + cmd + "\n" + output + error;
		dev_out.clear();
		return false;
	}
	return true;
}

static bool virtual_detach_tqt( const Glib::ustring &dev_path, int backend, Glib::ustring &error_msg )
{
	Glib::ustring output;
	Glib::ustring error;
	Glib::ustring cmd;
	if (backend == VBACKEND_LOOP)
		cmd = "losetup -d " + Glib::shell_quote( dev_path );
	else if (backend == VBACKEND_NBD)
		cmd = "qemu-nbd -d " + Glib::shell_quote( dev_path );
	else
		return true;
	const bool ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
		error_msg = "# " + cmd + "\n" + output + error;
	return ok;
}

Dialog_Imaging_Progress_TQt::ProgressWithText::ProgressWithText( TQWidget *parent )
	: TQWidget( parent ),
	  bar( 0 ),
	  label( 0 ),
	  pulse_pos( 0 ),
	  pulse_step( 10 )
{
	TQVBoxLayout *layout = new TQVBoxLayout( this );
	layout->setMargin( 0 );
	layout->setSpacing( 2 );

	label = new TQLabel( "", this );
	label->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	layout->addWidget( label );

	bar = new TQProgressBar( this );
	bar->setTotalSteps( 1000 );
	bar->setProgress( 0 );
	bar->setPercentageVisible( false );
	layout->addWidget( bar );
}

void Dialog_Imaging_Progress_TQt::ProgressWithText::set_fraction( double f )
{
	if (f < 0.0) f = 0.0;
	if (f > 1.0) f = 1.0;
	if (bar) bar->setProgress( (int)(f * 1000.0) );
}

void Dialog_Imaging_Progress_TQt::ProgressWithText::set_text( const TQString &t )
{
	if (label) label->setText( t );
}

void Dialog_Imaging_Progress_TQt::ProgressWithText::set_pulse_step( int step )
{
	pulse_step = step;
}

void Dialog_Imaging_Progress_TQt::ProgressWithText::pulse()
{
	pulse_pos += pulse_step;
	if (pulse_pos > 1000) pulse_pos = 0;
	if (bar) bar->setProgress( pulse_pos );
}

Dialog_Imaging_Progress_TQt::Dialog_Imaging_Progress_TQt( const TQString &title, const TQString &op_label, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_success( true ),
	  m_cancel( false ),
	  m_details_visible( false ),
	  m_running( false ),
	  m_force_cancel( false ),
	  m_last_bytes( 0 ),
	  m_last_secs( 0.0 ),
	  m_vbox( 0 ),
	  m_label_intro( 0 ),
	  m_label_current( 0 ),
	  m_progress_current( 0 ),
	  m_label_current_sub( 0 ),
	  m_label_completed( 0 ),
	  m_progress_all( 0 ),
	  m_expander_button( 0 ),
	  m_details_container( 0 ),
	  m_details_list( 0 ),
	  m_btn_cancel( 0 ),
	  m_btn_save( 0 ),
	  m_btn_close( 0 ),
	  m_cancel_timer( 0 ),
	  m_pulse_timer( 0 ),
	  m_cancel_countdown( 0 ),
	  m_compact_height( 0 ),
	  m_op_label( op_label ),
	  m_worker( 0 ),
	  m_ui_timer( 0 ),
	  m_icon_execute( load_icon_by_name( "gtk-execute" ) ),
	  m_icon_success( load_icon_by_name( "gtk-apply" ) ),
	  m_icon_error( load_icon_by_name( "gtk-dialog-error" ) ),
	  m_icon_info( load_icon_by_name( "gtk-dialog-info" ) ),
	  m_icon_warning( load_icon_by_name( "gtk-dialog-warning" ) )
{
	setCaption( title );
	setModal( true );
	if (!tdeparted_app_icon_pixmap().isNull())
		setIcon( tdeparted_app_icon_pixmap() );

	m_vbox = new TQVBoxLayout( this );
	m_vbox->setMargin( 10 );
	m_vbox->setSpacing( 5 );

	m_label_intro = new TQLabel( TQString::fromUtf8( _("This might take a long time.") ) + TQString::fromLatin1("\n"), this );
	m_label_intro->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	m_vbox->addWidget( m_label_intro );

	m_label_current = new TQLabel( "", this );
	m_label_current->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	{
		TQFont f = m_label_current->font();
		f.setBold( true );
		m_label_current->setFont( f );
	}
	if (!m_op_label.isEmpty())
		m_label_current->setText( m_op_label );
	m_vbox->addWidget( m_label_current );

	m_progress_current = new ProgressWithText( this );
	m_vbox->addWidget( m_progress_current );

	m_label_current_sub = new TQLabel( "", this );
	m_label_current_sub->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	{
		TQFont f = m_label_current_sub->font();
		f.setItalic( true );
		m_label_current_sub->setFont( f );
	}
	m_vbox->addWidget( m_label_current_sub );

	m_label_completed = new TQLabel( TQString::fromUtf8( _("Completed:") ), this );
	{
		TQFont f = m_label_completed->font();
		f.setBold( true );
		m_label_completed->setFont( f );
	}
	m_vbox->addWidget( m_label_completed );

	m_progress_all = new ProgressWithText( this );
	m_vbox->addWidget( m_progress_all );
	if (m_label_completed)
		m_label_completed->hide();
	if (m_progress_all)
		m_progress_all->hide();

	{
		TQHBoxLayout *eh = new TQHBoxLayout();
		eh->setMargin( 0 );
		eh->setSpacing( 4 );
		m_expander_button = new TQPushButton( TQString::fromUtf8( _("Details") ), this );
		m_expander_button->setToggleButton( true );
		m_expander_button->setOn( false );
		m_expander_button->setFlat( true );
		{
			TQFont f = m_expander_button->font();
			f.setBold( true );
			m_expander_button->setFont( f );
		}
		{
			TQPixmap pm = load_icon_by_name( "gtk-go-next" );
			if (pm.isNull())
				pm = load_icon_by_name( "go-next" );
			if (!pm.isNull())
				m_expander_button->setIconSet( TQIconSet( pm ) );
		}
		eh->addWidget( m_expander_button );
		eh->addStretch( 1 );
		m_vbox->addLayout( eh );
	}
	TQObject::connect( m_expander_button, TQT_SIGNAL(toggled(bool)), this, TQT_SLOT(on_details_toggled(bool)) );

	m_details_container = new TQWidget( this );
	{
		TQVBoxLayout *dv = new TQVBoxLayout( m_details_container );
		dv->setMargin( 0 );
		dv->setSpacing( 0 );

		m_details_list = new TQListView( m_details_container );
		m_details_list->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		m_details_list->setMinimumWidth( 700 );
		m_details_list->setSizePolicy( TQSizePolicy( TQSizePolicy::Expanding, TQSizePolicy::Expanding ) );
		m_details_list->addColumn( "" );
		m_details_list->addColumn( "" );
		m_details_list->addColumn( "" );
		if (m_details_list->header())
			m_details_list->header()->hide();
		m_details_list->setColumnWidthMode( 0, TQListView::Maximum );
		m_details_list->setColumnAlignment( 1, TQt::AlignRight );
		m_details_list->setAllColumnsShowFocus( true );
		m_details_list->setRootIsDecorated( true );
		dv->addWidget( m_details_list, 1 );
	}
	m_vbox->addWidget( m_details_container, 1 );
	m_details_container->hide();

	{
		TQHBoxLayout *hb = new TQHBoxLayout();
		hb->setMargin( 0 );
		hb->setSpacing( 6 );
		hb->addStretch( 1 );
		m_btn_cancel = new TQPushButton( TQString::fromUtf8( _("Cancel") ), this );
		m_btn_save = new TQPushButton( strip_gtk_mnemonic_underscores( TQString::fromUtf8( _("_Save Details") ) ), this );
		m_btn_close = new TQPushButton( TQString::fromUtf8( _("Close") ), this );
		m_btn_save->hide();
		m_btn_close->hide();
		hb->addWidget( m_btn_cancel );
		hb->addWidget( m_btn_save );
		hb->addWidget( m_btn_close );
		m_vbox->addLayout( hb );
	}
	TQObject::connect( m_btn_cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(on_cancel()) );
	TQObject::connect( m_btn_save,   TQT_SIGNAL(clicked()), this, TQT_SLOT(on_save()) );
	TQObject::connect( m_btn_close,  TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );

	m_cancel_timer = new TQTimer( this );
	TQObject::connect( m_cancel_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_cancel_timeout()) );
	m_pulse_timer = new TQTimer( this );
	TQObject::connect( m_pulse_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_pulse()) );

	resize( 700, sizeHint().height() );
}

bool Dialog_Imaging_Progress_TQt::run_modal_imaging( ImagingWorker_TQt *worker )
{
	m_worker = worker;
	TQTimer::singleShot( 0, this, TQT_SLOT(on_ui_timeout()) );
	exec();
	return m_success && !m_cancel;
}

void Dialog_Imaging_Progress_TQt::on_details_toggled( bool on )
{
	m_details_visible = on;
	if (m_expander_button)
	{
		TQPixmap pm = load_icon_by_name( on ? "gtk-go-down" : "gtk-go-next" );
		if (pm.isNull())
			pm = load_icon_by_name( on ? "go-down" : "go-next" );
		if (!pm.isNull())
			m_expander_button->setIconSet( TQIconSet( pm ) );
	}
	if (m_details_container)
	{
		if (on)
		{
			if (m_compact_height <= 0)
				m_compact_height = height();
			m_details_container->show();
			resize( width(), m_compact_height + 300 );
		}
		else
		{
			m_details_container->hide();
			if (m_compact_height > 0)
				resize( width(), m_compact_height );
		}
	}
}

static Glib::ustring get_home_dir_tqt()
{
	const char *h = getenv( "HOME" );
	if (h && *h)
		return Glib::ustring( h );
	struct passwd *pw = getpwuid( getuid() );
	if (pw && pw->pw_dir && *pw->pw_dir)
		return Glib::ustring( pw->pw_dir );
	return Glib::ustring();
}

static bool ensure_dir_exists_tqt( const Glib::ustring &path )
{
	if (path.empty())
		return false;
	if (mkdir( path.c_str(), 0755 ) == 0)
		return true;
	if (errno == EEXIST)
		return true;
	return false;
}

static Glib::ustring get_operations_log_path_tqt()
{
	const Glib::ustring home = get_home_dir_tqt();
	if (home.empty())
		return Glib::ustring();
	const Glib::ustring p1 = home + "/.local";
	const Glib::ustring p2 = p1 + "/share";
	const Glib::ustring p3 = p2 + "/tdeparted";
	if (!ensure_dir_exists_tqt( p1 ))
		return Glib::ustring();
	if (!ensure_dir_exists_tqt( p2 ))
		return Glib::ustring();
	if (!ensure_dir_exists_tqt( p3 ))
		return Glib::ustring();
	return p3 + "/operations.log";
}

static void append_operations_log_lines_tqt( std::ofstream &out, TQListView *details_list )
{
	if (!details_list)
		return;
	TQListViewItemIterator it( details_list );
	for ( ; it.current(); ++it )
	{
		const TQString t = it.current()->text(0);
		out << "  - " << t.local8Bit().data() << "\n";
	}
}

static void append_operations_log_tqt( const char *section, bool success, bool cancelled, const TQString &title, const OperationVector *ops, TQListView *details_list )
{
	const Glib::ustring log_path = get_operations_log_path_tqt();
	if (log_path.empty())
		return;
	std::ofstream out( log_path.c_str(), std::ios::out | std::ios::app );
	if (!out)
		return;

	char tbuf[64];
	tbuf[0] = 0;
	{
		time_t now = time( 0 );
		struct tm tmv;
		localtime_r( &now, &tmv );
		strftime( tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &tmv );
	}

	out << "[" << tbuf << "]";
	out << " [" << section << "]";
	out << " [" << (success ? "OK" : (cancelled ? "CANCEL" : "FAIL")) << "] ";
	out << title.local8Bit().data();
	out << "\n";

	if (ops)
	{
		out << "Operations:\n";
		for (unsigned int i = 0; i < ops->size(); i++)
		{
			const Operation *op = (*ops)[i].get();
			if (!op)
				continue;
			out << "  - " << op->m_description.c_str() << "\n";
		}
	}

	if (details_list)
	{
		out << "Details:\n";
		append_operations_log_lines_tqt( out, details_list );
	}
	out << "\n";
}

void Dialog_Imaging_Progress_TQt::on_cancel()
{
	if (!m_running)
		return;
	if (!m_cancel)
	{
		m_cancel = true;
		m_force_cancel = false;
		if (m_label_current_sub)
			m_label_current_sub->setText( TQString::fromUtf8( _("Cancelling operation... Please wait...") ) );
		if (m_btn_cancel)
			m_btn_cancel->setEnabled( false );
		if (m_worker)
			m_worker->cancel();
		m_cancel_countdown = 5;
		if (m_cancel_timer)
			m_cancel_timer->start( 1000, false );
		return;
	}

	// Second click => Force Cancel.
	// For safety, do not allow closing while a worker thread may still be writing to disk.
	// Request cancellation again and wait briefly for the thread to stop.
	m_force_cancel = true;
	if (m_cancel_timer && m_cancel_timer->isActive())
		m_cancel_timer->stop();
	if (m_btn_cancel)
	{
		m_btn_cancel->setText( TQString::fromUtf8( _("Force Cancel") ) );
		m_btn_cancel->setEnabled( false );
	}
	if (m_worker)
		m_worker->cancel();
	if (m_label_current_sub)
		m_label_current_sub->setText( TQString::fromUtf8( _("Force cancel requested... Waiting for worker to stop...") ) );

	{
		uint64_t t_ms = imaging_now_nsec() / 1000000ull;
		while (m_worker && m_worker->running())
		{
			const uint64_t now_ms = imaging_now_nsec() / 1000000ull;
			if (now_ms - t_ms >= 2000ull)
				break;
			usleep( 10000 );
		}
	}

	if (m_worker && !m_worker->running())
		on_worker_finished();
}

void Dialog_Imaging_Progress_TQt::on_cancel_timeout()
{
	if (m_force_cancel)
		return;
	m_cancel_countdown--;
	if (m_cancel_countdown <= 0)
	{
		if (m_cancel_timer)
			m_cancel_timer->stop();
		if (m_btn_cancel)
		{
			m_btn_cancel->setText( TQString::fromUtf8( _("Force Cancel") ) );
			m_btn_cancel->setEnabled( true );
		}
	}
}

void Dialog_Imaging_Progress_TQt::on_pulse()
{
	if (m_progress_current)
		m_progress_current->pulse();
}

void Dialog_Imaging_Progress_TQt::on_ui_timeout()
{
	if (!m_worker)
		return;

	if (!m_running)
	{
		m_running = true;
		m_success = true;
		m_cancel = false;
		m_last_bytes = 0;
		m_last_secs = 0.0;
		if (m_btn_cancel)
		{
			m_btn_cancel->setEnabled( true );
			m_btn_cancel->show();
		}
		if (m_btn_save)
			m_btn_save->hide();
		if (m_btn_close)
			m_btn_close->hide();
		if (m_progress_current)
		{
			m_progress_current->set_fraction( 0.0 );
			m_progress_current->set_text( TQString::fromLatin1(" ") );
		}
		if (m_progress_all)
		{
			m_progress_all->set_fraction( 0.0 );
			m_progress_all->set_text( TQString::fromLatin1(" ") );
		}
		if (m_label_current)
			m_label_current->setText( TQString::fromUtf8( _("In progress") ) );
		if (m_label_current_sub)
			m_label_current_sub->setText( "" );
		if (!m_op_label.isEmpty())
			m_label_current->setText( m_op_label );

		m_worker->start();
		m_ui_timer = new TQTimer( this );
		TQObject::connect( m_ui_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_ui_timeout()) );
		m_ui_timer->start( 100, false );
		return;
	}

	std::vector<ImagingUpdate_TQt> updates;
	m_worker->get_updates( updates );

	for (unsigned int i = 0; i < updates.size(); i++)
	{
		const ImagingUpdate_TQt &u = updates[i];
		const double frac = (u.bytes_total > 0) ? ((double)u.bytes_done / (double)u.bytes_total) : 0.0;

		if (m_progress_current)
			m_progress_current->set_fraction( frac );
		if (m_progress_all)
			m_progress_all->set_fraction( frac );

		double speed = 0.0;
		if (u.seconds_elapsed > m_last_secs && u.bytes_done > m_last_bytes)
			speed = (double)(u.bytes_done - m_last_bytes) / (u.seconds_elapsed - m_last_secs);
		m_last_bytes = u.bytes_done;
		m_last_secs = u.seconds_elapsed;

		if (m_label_current_sub)
		{
			if (speed > 0.0 && u.bytes_total > 0 && u.bytes_done < u.bytes_total)
			{
				const double rem = (double)(u.bytes_total - u.bytes_done);
				const double eta_s = rem / speed;
				char eb[64];
				const long eta = (long)(eta_s + 0.5);
				snprintf( eb, sizeof(eb), "ETA: %ld:%02ld:%02ld", eta / 3600l, (eta / 60l) % 60l, eta % 60l );
				m_label_current_sub->setText( TQString::fromLatin1( eb ) );
			}
			else if (m_cancel)
			{
				m_label_current_sub->setText( TQString::fromUtf8( _("Cancelling operation... Please wait...") ) );
			}
		}

		TQString txt = TQString::fromUtf8( Glib::ustring::compose( "%1/%2 MiB", (u.bytes_done >> 20), (u.bytes_total >> 20) ).c_str() );
		if (speed > 0.0)
		{
			const double mibs = speed / (1024.0 * 1024.0);
			txt += TQString::fromLatin1("  ");
			char sbuf[64];
			snprintf( sbuf, sizeof(sbuf), "%.1f MiB/s", mibs );
			txt += TQString::fromLatin1( sbuf );
		}
		if (m_progress_current)
			m_progress_current->set_text( txt + TQString::fromLatin1(" ") );
		if (m_progress_all)
			m_progress_all->set_text( txt + TQString::fromLatin1(" ") );

		if (u.error_code != 0)
		{
			m_success = false;
			if (m_expander_button)
				m_expander_button->setOn( true );
			if (m_details_list)
			{
				TQListViewItem *it = new TQListViewItem( m_details_list );
				it->setText( 0, TQString::fromUtf8( u.error_context.c_str() ) );
				it->setText( 1, TQString::fromLatin1( "" ) );
				if (!m_icon_error.isNull())
					it->setPixmap( 2, m_icon_error );
			}
		}
		else
		{
			if (m_details_list)
			{
				TQListViewItem *it = new TQListViewItem( m_details_list );
				it->setText( 0, TQString::fromUtf8( Glib::ustring::compose( _("Copied %1 bytes"), u.bytes_done ).c_str() ) );
				it->setText( 1, TQString::fromLatin1( "" ) );
				if (!m_icon_execute.isNull())
					it->setPixmap( 2, m_icon_execute );
			}
		}
	}

	if ( !m_worker->running() )
	{
		m_success = m_worker->get_success();
		if (m_worker->get_cancelled())
			m_cancel = true;
		on_worker_finished();
	}
}

void Dialog_Imaging_Progress_TQt::on_worker_finished()
{
	m_running = false;
	if (m_ui_timer && m_ui_timer->isActive())
		m_ui_timer->stop();
	if (m_pulse_timer && m_pulse_timer->isActive())
		m_pulse_timer->stop();

	if (m_btn_cancel)
		m_btn_cancel->hide();
	if (m_btn_save)
		m_btn_save->show();
	if (m_btn_close)
		m_btn_close->show();

	if (m_cancel)
	{
		if (m_progress_current)
		{
			m_progress_current->set_text( TQString::fromUtf8( _("Operation cancelled") ) );
			m_progress_current->set_fraction( 0 );
		}
		if (m_label_current_sub)
			m_label_current_sub->setText( "" );
	}
	else
	{
		if (m_success)
		{
			if (m_progress_all)
			{
				m_progress_all->set_text( TQString::fromUtf8( _("Completed") ) );
				m_progress_all->set_fraction( 1.0 );
			}
		}
		else
		{
			if (m_progress_all)
				m_progress_all->set_text( TQString::fromUtf8( _("Error") ) );
		}
	}

	if (m_worker)
	{
		m_worker->wait();
		delete m_worker;
		m_worker = 0;
	}

	append_operations_log_tqt( "imaging", m_success, m_cancel, caption(), 0, m_details_list );
}

void Dialog_Imaging_Progress_TQt::on_save()
{
	const TQString filename = TQFileDialog::getSaveFileName(
		TQString::fromLatin1("tdeparted_imaging_details.txt"),
		TQString::fromLatin1("Text (*.txt);;All Files (*)"),
		this,
		"save_imaging_details",
		TQString::fromUtf8( _("Save Details") ) );
	if (filename.isEmpty())
		return;
	std::ofstream out( filename.local8Bit().data() );
	if (!out)
	{
		TQMessageBox::critical( this, TQString::fromUtf8( _("Save Details") ), tr("Failed to open file for writing"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (m_details_list)
	{
		TQListViewItemIterator it( m_details_list );
		for ( ; it.current(); ++it )
			out << it.current()->text(0).local8Bit().data() << "\n";
	}
	out.close();
	if (!out)
		TQMessageBox::critical( this, TQString::fromUtf8( _("Save Details") ), tr("Failed to write file"), TQMessageBox::Ok, TQMessageBox::NoButton );
}

void Dialog_Imaging_Progress_TQt::closeEvent( TQCloseEvent *e )
{
	if (m_running)
		e->ignore();
	else
		TQDialog::closeEvent( e );
}

void Dialog_Imaging_Progress_TQt::accept()
{
	if (m_running)
		return;
	TQDialog::accept();
}

static bool read_sysfs_trimmed_tqt( const char *path, TQString &out )
{
	out = TQString::null;
	std::ifstream in( path );
	if (!in)
		return false;
	std::string s;
	std::getline( in, s );
	while (!s.empty() && (s.back() == '\n' || s.back() == '\r'))
		s.pop_back();
	out = TQString::fromLatin1( s.c_str() );
	return true;
}

static bool sysfs_block_path_contains_usb_tqt( const TQString &block_name )
{
	char linkpath[256];
	snprintf( linkpath, sizeof(linkpath), "/sys/block/%s", block_name.latin1() );
	char buf[PATH_MAX + 1];
	const ssize_t n = readlink( linkpath, buf, PATH_MAX );
	if (n <= 0)
		return false;
	buf[n] = 0;
	const TQString p = TQString::fromLocal8Bit( buf );
	return p.find( "/usb" ) >= 0 || p.find( "usb" ) >= 0;
}

static DeviceType_TQt detect_device_type_tqt( const Glib::ustring &device_path )
{
	if (device_path.empty())
		return DEVTYPE_UNKNOWN;
	TQString base = TQString::fromUtf8( device_path.c_str() );
	if (base.startsWith( "/dev/" ))
		base = base.mid( 5 );
	if (base.isEmpty())
		return DEVTYPE_UNKNOWN;

	if (sysfs_block_path_contains_usb_tqt( base ))
		return DEVTYPE_USB_STORAGE;

	if (base.startsWith( "nvme" ))
		return DEVTYPE_NVME_SSD;

	char rotpath[256];
	snprintf( rotpath, sizeof(rotpath), "/sys/block/%s/queue/rotational", base.latin1() );
	TQString rotational;
	if (read_sysfs_trimmed_tqt( rotpath, rotational ))
	{
		const int rot = rotational.toInt();
		if (rot == 0)
			return DEVTYPE_SATA_SSD;
		if (rot == 1)
			return DEVTYPE_MECHANICAL;
	}
	return DEVTYPE_UNKNOWN;
}

static std::string html_escape( const Glib::ustring &s )
{
	std::string out;
	out.reserve( s.size() );
	for (Glib::ustring::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		const gunichar c = *it;
		if      (c == '&')  out += "&amp;";
		else if (c == '<')  out += "&lt;";
		else if (c == '>')  out += "&gt;";
		else if (c == '"')  out += "&quot;";
		else                out += std::string( it.base(), (++Glib::ustring::const_iterator(it)).base() );
	}
	return out;
}

static void write_device_details_html_tqt( const Device &device, std::ofstream &out )
{
	out << "<table>\n";
	out << "<tr><th>Device:</th><td>" << html_escape( device.get_path() ) << "</td></tr>\n";
	out << "<tr><th>Model:</th><td>" << html_escape( device.model ) << "</td></tr>\n";
	out << "<tr><th>Serial:</th><td>" << html_escape( device.serial_number ) << "</td></tr>\n";
	out << "<tr><th>Sector size:</th><td>" << device.sector_size << "</td></tr>\n";
	out << "<tr><th>Total sectors:</th><td>" << device.length << "</td></tr>\n";
	out << "<tr><td colspan='2'>&nbsp;</td></tr>\n";
	out << "<tr><th>Heads:</th><td>" << device.heads << "</td></tr>\n";
	out << "<tr><th>Sectors/track:</th><td>" << device.sectors << "</td></tr>\n";
	out << "<tr><th>Cylinders:</th><td>" << device.cylinders << "</td></tr>\n";
	out << "<tr><td colspan='2'>&nbsp;</td></tr>\n";
	out << "<tr><th>Partition table:</th><td>" << html_escape( device.disktype ) << "</td></tr>\n";
	out << "</table>\n";
}

static void write_operation_details_html_tqt( const OperationDetail &od, std::ofstream &out )
{
	Glib::ustring temp = od.get_description();
	for (unsigned int index = temp.find("\n"); index < temp.length(); index = temp.find("\n"))
		temp.replace( index, 1, "<br />" );

	out << "<table>\n<tr>\n<td colspan='2'>\n" << temp;
	if (!od.get_elapsed_time().empty())
		out << "&nbsp;&nbsp;" << od.get_elapsed_time();
	out << "\n</td>\n</tr>\n";

	if (od.get_children().size())
	{
		out << "<tr>\n<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>\n<td>\n";
		for (unsigned int i = 0; i < od.get_children().size(); i++)
			write_operation_details_html_tqt( *(od.get_children()[i]), out );
		out << "</td>\n</tr>\n";
	}
	out << "</table>\n";
}

static TQString strip_simple_pango_markup( const Glib::ustring &in )
{
	TQString s = TQString::fromUtf8( in.c_str() );
	// Decode a minimal set of XML/HTML entities that appear in operation detail strings.
	// Keep this local and simple: GParted operation details are plain text with occasional
	// markup and entity escaping.
	s.replace( TQString::fromLatin1("&apos;"), TQString::fromLatin1("'") );
	s.replace( TQString::fromLatin1("&quot;"), TQString::fromLatin1("\"") );
	s.replace( TQString::fromLatin1("&lt;"),   TQString::fromLatin1("<") );
	s.replace( TQString::fromLatin1("&gt;"),   TQString::fromLatin1(">") );
	s.replace( TQString::fromLatin1("&amp;"),  TQString::fromLatin1("&") );
	// Numeric entities (best effort).
	{
		int start = 0;
		while ((start = s.find( TQString::fromLatin1("&#"), start )) != -1)
		{
			const int semi = s.find( ';', start + 2 );
			if (semi == -1)
				break;
			const TQString num = s.mid( start + 2, semi - (start + 2) );
			bool ok = false;
			uint code = 0;
			if (num.length() > 1 && (num[0] == 'x' || num[0] == 'X'))
				code = num.mid(1).toUInt( &ok, 16 );
			else
				code = num.toUInt( &ok, 10 );
			if (!ok)
			{
				start = semi + 1;
				continue;
			}
			const TQString repl( TQChar( (ushort)(code & 0xFFFFu) ) );
			s.replace( start, semi - start + 1, repl );
			start += repl.length();
		}
	}
	TQString out;
	out.reserve( s.length() );
	bool in_tag = false;
	for (int i = 0; i < (int)s.length(); i++)
	{
		const TQChar c = s[i];
		if (!in_tag)
		{
			if (c == '<')
				in_tag = true;
			else
				out += c;
		}
		else
		{
			if (c == '>')
				in_tag = false;
		}
	}
	return out;
}

/* ---------------------------------------------------------------------------
 * Dialog_Progress_TQt — faithful reproduction of GTK Dialog_Progress layout
 *
 * Widget hierarchy (mirrors GTK):
 *
 *   TQDialog
 *   └── m_vbox (margin=10, spacing=5)
 *       ├── m_label_intro           "Depending on the number and type..."
 *       ├── m_label_current         bold: current operation description
 *       ├── m_progressbar_current   progress bar (pulsable, text overlay)
 *       ├── m_label_current_sub     italic: current sub-operation
 *       ├── m_label_completed       bold "Completed Operations:"
 *       ├── m_progressbar_all       overall progress bar (text overlay)
 *       ├── [expander_row]          ▶/▼ "Details" (left-aligned)
 *       ├── m_details_container     ScrolledWindow + TQListView (3 cols)
 *       └── [button_row]            Cancel → then Save Details + Close
 * ---------------------------------------------------------------------------*/

Dialog_Progress_TQt::ProgressWithText::ProgressWithText( TQWidget *parent )
	: TQWidget( parent ),
	  bar( 0 ),
	  label( 0 ),
	  pulse_pos( 0 ),
	  pulse_step( 10 )
{
	TQVBoxLayout *layout = new TQVBoxLayout( this );
	layout->setMargin( 0 );
	layout->setSpacing( 2 );

	label = new TQLabel( "", this );
	label->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	layout->addWidget( label );

	bar = new TQProgressBar( this );
	bar->setTotalSteps( 1000 );
	bar->setProgress( 0 );
	bar->setPercentageVisible( false );
	layout->addWidget( bar );
}

void Dialog_Progress_TQt::ProgressWithText::set_fraction( double f )
{
	if (f < 0.0) f = 0.0;
	if (f > 1.0) f = 1.0;
	if (bar) bar->setProgress( (int)(f * 1000.0) );
}

void Dialog_Progress_TQt::ProgressWithText::set_text( const TQString &t )
{
	if (label) label->setText( t );
}

void Dialog_Progress_TQt::ProgressWithText::set_pulse_step( int step )
{
	pulse_step = step;
}

void Dialog_Progress_TQt::ProgressWithText::pulse()
{
	pulse_pos += pulse_step;
	if (pulse_pos > 1000) pulse_pos = 0;
	if (bar) bar->setProgress( pulse_pos );
}

Dialog_Progress_TQt::Dialog_Progress_TQt( const std::vector<Device> &devices, const OperationVector &operations, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_devices( devices ),
	  m_operations( operations ),
	  m_success( true ),
	  m_cancel( false ),
	  m_curr_op( 0 ),
	  m_warnings( 0 ),
	  m_details_visible( false ),
	  m_running( false ),
	  m_force_cancel( false ),
	  m_core( 0 ),
	  m_vbox( 0 ),
	  m_label_intro( 0 ),
	  m_label_current( 0 ),
	  m_progress_current( 0 ),
	  m_label_current_sub( 0 ),
	  m_label_completed( 0 ),
	  m_progress_all( 0 ),
	  m_expander_button( 0 ),
	  m_details_container( 0 ),
	  m_details_list( 0 ),
	  m_btn_cancel( 0 ),
	  m_btn_save( 0 ),
	  m_btn_close( 0 ),
	  m_cancel_timer( 0 ),
	  m_pulse_timer( 0 ),
	  m_cancel_countdown( 0 ),
	  m_compact_height( 0 ),
	  m_icon_execute( load_icon_by_name( "gtk-execute" ) ),
	  m_icon_success( load_icon_by_name( "gtk-apply" ) ),
	  m_icon_error( load_icon_by_name( "gtk-dialog-error" ) ),
	  m_icon_info( load_icon_by_name( "gtk-dialog-info" ) ),
	  m_icon_warning( load_icon_by_name( "gtk-dialog-warning" ) )
{
	setCaption( tr("Applying pending operations") );
	setModal( true );
	if (!tdeparted_app_icon_pixmap().isNull())
		setIcon( tdeparted_app_icon_pixmap() );

	/* ---- Main VBox (GTK: vbox border_width=10, spacing=5) ---- */
	m_vbox = new TQVBoxLayout( this );
	m_vbox->setMargin( 10 );
	m_vbox->setSpacing( 5 );

	/* ---- Intro label ---- */
	m_label_intro = new TQLabel(
		TQString::fromUtf8( _("Depending on the number and type of operations this might take a long time.") )
		+ TQString::fromLatin1("\n"),
		this );
	m_label_intro->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	m_vbox->addWidget( m_label_intro );

	/* ---- Current operation label (bold) ---- */
	m_label_current = new TQLabel( "", this );
	m_label_current->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	{
		TQFont f = m_label_current->font();
		f.setBold( true );
		m_label_current->setFont( f );
	}
	m_vbox->addWidget( m_label_current );

	/* ---- Current progress bar (GTK: set_pulse_step=0.01, set_show_text) ---- */
	m_progress_current = new ProgressWithText( this );
	m_vbox->addWidget( m_progress_current );

	/* ---- Current sub-operation label (italic) ---- */
	m_label_current_sub = new TQLabel( "", this );
	m_label_current_sub->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
	{
		TQFont f = m_label_current_sub->font();
		f.setItalic( true );
		m_label_current_sub->setFont( f );
	}
	m_vbox->addWidget( m_label_current_sub );

	/* ---- "Completed Operations:" label (bold) ---- */
	m_label_completed = new TQLabel(
		TQString::fromUtf8( _("Completed Operations:") ), this );
	{
		TQFont f = m_label_completed->font();
		f.setBold( true );
		m_label_completed->setFont( f );
	}
	m_vbox->addWidget( m_label_completed );

	/* ---- Overall progress bar (GTK: set_show_text) ---- */
	m_progress_all = new ProgressWithText( this );
	m_vbox->addWidget( m_progress_all );

	/* ---- Expander "Details" (left-aligned, bold, triangle icon) ---- */
	{
		TQHBoxLayout *eh = new TQHBoxLayout();
		eh->setMargin( 0 );
		eh->setSpacing( 4 );
		m_expander_button = new TQPushButton( TQString::fromUtf8( _("Details") ), this );
		m_expander_button->setToggleButton( true );
		m_expander_button->setOn( false );
		m_expander_button->setFlat( true );
		{
			TQFont f = m_expander_button->font();
			f.setBold( true );
			m_expander_button->setFont( f );
		}
		{
			TQPixmap pm = load_icon_by_name( "gtk-go-next" );
			if (pm.isNull())
				pm = load_icon_by_name( "go-next" );
			if (!pm.isNull())
				m_expander_button->setIconSet( TQIconSet( pm ) );
		}
		eh->addWidget( m_expander_button );
		eh->addStretch( 1 );
		m_vbox->addLayout( eh );
	}
	TQObject::connect( m_expander_button, TQT_SIGNAL(toggled(bool)),
	                  this, TQT_SLOT(on_details_toggled(bool)) );

	/* ---- Details container (GTK: ScrolledWindow 700×250, ETCHED_IN) ---- */
	m_details_container = new TQWidget( this );
	{
		TQVBoxLayout *dv = new TQVBoxLayout( m_details_container );
		dv->setMargin( 0 );
		dv->setSpacing( 0 );

		m_details_list = new TQListView( m_details_container );
		m_details_list->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		m_details_list->setMinimumWidth( 700 );
		m_details_list->setSizePolicy( TQSizePolicy( TQSizePolicy::Expanding, TQSizePolicy::Expanding ) );
		m_details_list->addColumn( "" );  // col 0: description (expand)
		m_details_list->addColumn( "" );  // col 1: elapsed time
		m_details_list->addColumn( "" );  // col 2: status icon
		if (m_details_list->header())
			m_details_list->header()->hide();
		m_details_list->setColumnWidthMode( 0, TQListView::Maximum );
		m_details_list->setColumnAlignment( 1, TQt::AlignRight );
		m_details_list->setAllColumnsShowFocus( true );
		m_details_list->setRootIsDecorated( true );
		dv->addWidget( m_details_list, 1 );
	}
	m_vbox->addWidget( m_details_container, 1 );
	m_details_container->hide();

	/* ---- Buttons row (GTK: Cancel during run, Save+Close after) ---- */
	{
		TQHBoxLayout *hb = new TQHBoxLayout();
		hb->setMargin( 0 );
		hb->setSpacing( 6 );
		hb->addStretch( 1 );
		m_btn_cancel = new TQPushButton(
			TQString::fromUtf8( _("Cancel") ), this );
		m_btn_save = new TQPushButton(
			strip_gtk_mnemonic_underscores(
				TQString::fromUtf8( _("_Save Details") ) ), this );
		m_btn_close = new TQPushButton(
			TQString::fromUtf8( _("Close") ), this );
		m_btn_save->hide();
		m_btn_close->hide();
		hb->addWidget( m_btn_cancel );
		hb->addWidget( m_btn_save );
		hb->addWidget( m_btn_close );
		m_vbox->addLayout( hb );
	}
	TQObject::connect( m_btn_cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(on_cancel()) );
	TQObject::connect( m_btn_save,   TQT_SIGNAL(clicked()), this, TQT_SLOT(on_save()) );
	TQObject::connect( m_btn_close,  TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );

	/* ---- Timers ---- */
	m_cancel_timer = new TQTimer( this );
	TQObject::connect( m_cancel_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_cancel_timeout()) );
	m_pulse_timer = new TQTimer( this );
	TQObject::connect( m_pulse_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_pulse()) );

	/* ---- Seed the details treeview with one top-level row per operation ---- */
	for (unsigned int i = 0; i < m_operations.size(); i++)
	{
		m_operations[i]->m_operation_detail.set_description( m_operations[i]->m_description, FONT_BOLD );
		m_operations[i]->m_operation_detail.set_treepath( Utils::num_to_str(i) );

		TQListViewItem *it = new TQListViewItem( m_details_list );
		it->setText( 0, strip_simple_pango_markup( m_operations[i]->m_operation_detail.get_description() ) );
		it->setMultiLinesEnabled( true );
		m_items[m_operations[i]->m_operation_detail.get_treepath()] = it;
	}

	/* ---- Initial compact size (GTK: default_width=700) ---- */
	resize( 700, sizeHint().height() );
}

bool Dialog_Progress_TQt::run_modal_apply( GParted_Core &core )
{
	m_core = &core;
	TQTimer::singleShot( 0, this, TQT_SLOT(on_start_apply()) );
	exec();
	return m_success && !m_cancel;
}

void Dialog_Progress_TQt::on_details_toggled( bool on )
{
	m_details_visible = on;

	/* Update expander arrow icon */
	if (m_expander_button)
	{
		TQPixmap pm = load_icon_by_name( on ? "gtk-go-down" : "gtk-go-next" );
		if (pm.isNull())
			pm = load_icon_by_name( on ? "go-down" : "go-next" );
		if (!pm.isNull())
			m_expander_button->setIconSet( TQIconSet( pm ) );
	}

	if (m_details_container)
	{
		if (on)
		{
			/* Remember compact height before expanding */
			if (m_compact_height <= 0)
				m_compact_height = height();
			m_details_container->show();
			/* Grow the dialog to show 250px of detail tree */
			resize( width(), m_compact_height + 300 );
		}
		else
		{
			m_details_container->hide();
			if (m_compact_height > 0)
				resize( width(), m_compact_height );
		}
	}
}

ApplyWorker_TQt::ApplyWorker_TQt( GParted_Core *core, const OperationVector &operations )
	: m_core( core ),
	  m_operations( operations ),
	  m_success( false ),
	  m_cancel_requested( false ),
	  m_current_op( 0 )
{
}

void ApplyWorker_TQt::run()
{
	m_state_mutex.lock();
	m_success = true;
	m_cancel_requested = false;
	m_state_mutex.unlock();

	for ( int idx = 0; ; idx++ )
	{
		m_state_mutex.lock();
		const bool cancel_now = m_cancel_requested;
		const bool ok_so_far = m_success;
		m_current_op = idx;
		m_state_mutex.unlock();

		if (idx >= (int)m_operations.size() || !ok_so_far || cancel_now)
			break;

		sigc::connection conn = m_operations[idx]->m_operation_detail.signal_update.connect(
			sigc::mem_fun( *this, &ApplyWorker_TQt::on_signal_update ) );

		m_operations[idx]->m_operation_detail.set_status( STATUS_EXECUTE );
		const bool ok = m_core->apply_operation_to_disk( m_operations[idx].get() );
		m_operations[idx]->m_operation_detail.set_success_and_capture_errors( ok );

		m_state_mutex.lock();
		m_success = ok;
		m_state_mutex.unlock();
		conn.disconnect();
	}
}

void ApplyWorker_TQt::cancel()
{
	m_state_mutex.lock();
	m_cancel_requested = true;
	const int idx = m_current_op;
	m_state_mutex.unlock();

	if (idx >= 0 && idx < (int)m_operations.size())
		m_operations[idx]->m_operation_detail.signal_cancel( true );
}

int ApplyWorker_TQt::get_current_op()
{
	m_state_mutex.lock();
	const int v = m_current_op;
	m_state_mutex.unlock();
	return v;
}

bool ApplyWorker_TQt::get_success()
{
	m_state_mutex.lock();
	const bool v = m_success;
	m_state_mutex.unlock();
	return v;
}

void ApplyWorker_TQt::get_updates( std::vector<OpsUpdate_TQt> &updates )
{
	m_queue_mutex.lock();
	updates = m_update_queue;
	m_update_queue.clear();
	m_queue_mutex.unlock();
}

void ApplyWorker_TQt::on_signal_update( const OperationDetail &od )
{
	m_state_mutex.lock();
	const bool cancel_now = m_cancel_requested;
	m_state_mutex.unlock();
	if ( cancel_now )
		od.signal_cancel( true );

	OpsUpdate_TQt update;
	update.treepath = od.get_treepath();
	update.description = od.get_description();
	update.elapsed = od.get_elapsed_time();
	update.status = od.get_status();

	const ProgressBar &pb = od.get_progressbar();
	update.pb_running = pb.running() ? 1 : 0;
	update.fraction = pb.get_fraction();
	update.pb_text = pb.get_text();

	m_queue_mutex.lock();
	m_update_queue.push_back( update );
	m_queue_mutex.unlock();
}

void Dialog_Progress_TQt::on_start_apply()
{
	m_running = true;
	m_success = true;
	m_cancel = false;
	m_curr_op = 0;
	m_warnings = 0;
	m_cancel_countdown = 0;

	if (m_cancel_timer && m_cancel_timer->isActive())
		m_cancel_timer->stop();
	if (m_pulse_timer && m_pulse_timer->isActive())
		m_pulse_timer->stop();

	if (m_btn_cancel)
	{
		m_btn_cancel->setText( TQString::fromUtf8( _("Cancel") ) );
		m_btn_cancel->setEnabled( true );
		m_btn_cancel->show();
	}
	if (m_btn_save)
		m_btn_save->hide();
	if (m_btn_close)
		m_btn_close->hide();

	if (m_progress_current)
	{
		m_progress_current->set_fraction( 0 );
		m_progress_current->set_text( TQString::fromLatin1(" ") );
	}

	const double frac = (m_operations.size() > 0) ? (1.0 / (double)m_operations.size()) : 1.0;
	TQString all_text = TQString::fromUtf8(
		Glib::ustring::compose( _("%1 of %2 operations completed"),
		                        m_curr_op, m_operations.size() ).c_str() );
	if (m_progress_all)
	{
		m_progress_all->set_text( all_text );
		m_progress_all->set_fraction( frac * (double)m_curr_op );
	}

	if (m_operations.size() > 0)
	{
		if (m_label_current)
			m_label_current->setText( strip_simple_pango_markup( m_operations[0]->m_description ) );
	}

	if (!m_core)
		return;

	m_worker = new ApplyWorker_TQt( m_core, m_operations );
	m_worker->start();

	m_ui_timer = new TQTimer( this );
	TQObject::connect( m_ui_timer, TQT_SIGNAL(timeout()), this, TQT_SLOT(on_ui_timeout()) );
	m_ui_timer->start( 100, false );
}

void Dialog_Progress_TQt::on_worker_finished()
{
	m_running = false;
	if (m_ui_timer && m_ui_timer->isActive())
		m_ui_timer->stop();
	if (m_pulse_timer && m_pulse_timer->isActive())
		m_pulse_timer->stop();

	if (m_btn_cancel)
		m_btn_cancel->hide();
	if (m_btn_save)
		m_btn_save->show();
	if (m_btn_close)
		m_btn_close->show();

	if (m_cancel)
	{
		if (m_progress_current)
		{
			m_progress_current->set_text( TQString::fromUtf8( _("Operation cancelled") ) );
			m_progress_current->set_fraction( 0 );
		}
	}
	else
	{
		if (m_label_current)
			m_label_current->hide();
		if (m_progress_current)
			m_progress_current->hide();
		if (m_label_current_sub)
			m_label_current_sub->hide();
	}

	if (m_success)
	{
		TQString done = TQString::fromUtf8( _("All operations successfully completed") );
		if (m_warnings > 0)
			done += TQString::fromLatin1(" (")
			     + TQString::number( (int)m_warnings )
			     + TQString::fromUtf8( _(" warnings") )
			     + TQString::fromLatin1(")");
		if (m_progress_all)
		{
			m_progress_all->set_text( done );
			m_progress_all->set_fraction( 1.0 );
		}
	}
	else if (!m_cancel)
	{
		if (m_expander_button)
			m_expander_button->setOn( true );
	}

	int unexecuted = (int)m_operations.size() - m_curr_op;
	if ( (!m_success || m_cancel) && unexecuted > 0 )
	{
		TQString msg;
		if (m_cancel)
		{
			msg  = TQString::fromUtf8( _("Operation canceled.") );
			msg += TQString::fromLatin1("\n\n");
			msg += TQString::fromUtf8( Glib::ustring::compose( _("%1 pending operations were removed from the queue without being executed."), unexecuted ).c_str() );
			TQMessageBox::information( this, TQString::fromUtf8( _("Cancel") ), msg, TQMessageBox::Ok, TQMessageBox::NoButton );
		}
		else
		{
			msg  = TQString::fromUtf8( _("An error occurred while applying operations.") );
			msg += TQString::fromLatin1("\n\n");
			msg += TQString::fromUtf8( Glib::ustring::compose( _("%1 pending operations were removed from the queue without being executed."), unexecuted ).c_str() );
			TQMessageBox::warning( this, TQString::fromUtf8( _("Error") ), msg, TQMessageBox::Ok, TQMessageBox::NoButton );
		}
	}

	m_compact_height = 0;

	if (m_worker)
	{
		m_worker->wait();
		delete m_worker;
		m_worker = 0;
	}

	append_operations_log_tqt( "apply", m_success, m_cancel, caption(), &m_operations, m_details_list );
}

void Dialog_Progress_TQt::on_cancel()
{
	const int r = TQMessageBox::warning(
		this,
		TQString::fromUtf8( _("Cancel") ),
		TQString::fromUtf8( _("Are you sure you want to cancel the current operation?") )
		+ TQString::fromLatin1("\n\n")
		+ TQString::fromUtf8( _("Canceling an operation might cause SEVERE file system damage.") ),
		TQString::fromUtf8( _("Continue Operation") ),
		TQString::fromUtf8( _("Cancel Operation") ) );
	if (r == 0)
		return;
	if (!m_cancel || r != 0)
	{
		if (m_btn_cancel)
			m_btn_cancel->setEnabled( false );
		if (!m_cancel)
		{
			m_cancel_countdown = 5;
			if (m_btn_cancel)
				m_btn_cancel->setText(
					TQString::fromUtf8(
						Glib::ustring::compose( _("Force Cancel (%1)"), m_cancel_countdown ).c_str() ) );
			if (m_cancel_timer)
				m_cancel_timer->start( 1000, false );
			m_cancel = true;
			if (m_curr_op < (unsigned int)m_operations.size())
				m_operations[m_curr_op]->m_operation_detail.signal_cancel( false );
		}
		else
		{
			if (m_btn_cancel)
				m_btn_cancel->setText( TQString::fromUtf8( _("Force Cancel") ) );
			force_cancel_current();
		}
	}
}

void Dialog_Progress_TQt::on_cancel_timeout()
{
	if (m_force_cancel)
	{
		if (m_cancel_timer && m_cancel_timer->isActive())
			m_cancel_timer->stop();
		return;
	}
	if (--m_cancel_countdown)
	{
		if (m_btn_cancel)
			m_btn_cancel->setText(
				TQString::fromUtf8(
					Glib::ustring::compose( _("Force Cancel (%1)"), m_cancel_countdown ).c_str() ) );
	}
	else
	{
		if (m_btn_cancel)
			m_btn_cancel->setText( TQString::fromUtf8( _("Force Cancel") ) );
		if (m_cancel_timer)
			m_cancel_timer->stop();
		if (m_btn_cancel)
			m_btn_cancel->setEnabled( true );
	}
}

void Dialog_Progress_TQt::on_pulse()
{
	/* Pulse only the current progress bar when indeterminate */
	if (m_progress_current)
		m_progress_current->pulse();
}

void Dialog_Progress_TQt::force_cancel_current()
{
	if (m_worker)
		m_worker->cancel();
	m_force_cancel = true;
	if (m_cancel_timer && m_cancel_timer->isActive())
		m_cancel_timer->stop();
	if (m_btn_cancel)
	{
		m_btn_cancel->setText( TQString::fromUtf8( _("Force Cancel") ) );
		m_btn_cancel->setEnabled( false );
	}
	if (m_pulse_timer && m_pulse_timer->isActive())
		m_pulse_timer->stop();
	if (m_label_current_sub)
		m_label_current_sub->setText( TQString::fromUtf8( _("Force cancel requested... Waiting for worker to stop...") ) );

	{
		const uint64_t t_ms = imaging_now_nsec() / 1000000ull;
		while (m_worker && m_worker->running())
		{
			const uint64_t now_ms = imaging_now_nsec() / 1000000ull;
			if (now_ms - t_ms >= 2000ull)
				break;
			usleep( 10000 );
		}
	}

	if (m_worker && !m_worker->running())
		on_worker_finished();
}

void Dialog_Progress_TQt::on_ui_timeout()
{
	if (!m_worker)
		return;

	std::vector<OpsUpdate_TQt> updates;
	m_worker->get_updates( updates );

	for ( unsigned int i = 0; i < updates.size(); i++ )
	{
		const OpsUpdate_TQt &upd = updates[i];

		TQListViewItem *it = 0;
		std::map<Glib::ustring, TQListViewItem*>::iterator f = m_items.find( upd.treepath );
		if (f != m_items.end())
		{
			it = f->second;
		}
		else
		{
			Glib::ustring parent_path = upd.treepath;
			const std::size_t pos = parent_path.rfind( ':' );
			if (pos != Glib::ustring::npos)
				parent_path = parent_path.substr( 0, pos );
			std::map<Glib::ustring, TQListViewItem*>::iterator p = m_items.find( parent_path );
			if (p != m_items.end())
				it = new TQListViewItem( p->second );
			else
				it = new TQListViewItem( m_details_list );
			it->setMultiLinesEnabled( true );
			m_items[upd.treepath] = it;
		}

		it->setText( 0, strip_simple_pango_markup( upd.description ) );
		it->setText( 1, TQString::fromUtf8( upd.elapsed.c_str() ) );
		it->setText( 2, TQString::fromLatin1("") );

		switch (upd.status)
		{
			case STATUS_EXECUTE: if (!m_icon_execute.isNull()) it->setPixmap( 2, m_icon_execute ); break;
			case STATUS_SUCCESS: if (!m_icon_success.isNull()) it->setPixmap( 2, m_icon_success ); break;
			case STATUS_ERROR:   if (!m_icon_error.isNull())   it->setPixmap( 2, m_icon_error );   break;
			case STATUS_INFO:    if (!m_icon_info.isNull())     it->setPixmap( 2, m_icon_info );    break;
			case STATUS_WARNING: if (!m_icon_warning.isNull())  { it->setPixmap( 2, m_icon_warning ); m_warnings++; } break;
			case STATUS_NONE: default: break;
		}

		if (upd.pb_running)
		{
			if (m_pulse_timer && m_pulse_timer->isActive())
				m_pulse_timer->stop();
			if (m_progress_current)
			{
				m_progress_current->set_fraction( upd.fraction );
				m_progress_current->set_text(
					strip_simple_pango_markup( upd.pb_text ) + TQString::fromLatin1(" ") );
			}
		}
		else
		{
			if (m_pulse_timer && !m_pulse_timer->isActive())
			{
				if (m_progress_current)
					m_progress_current->set_text( TQString::fromLatin1(" ") );
				m_pulse_timer->start( 100, false );
			}
		}

		if (upd.status == STATUS_EXECUTE)
		{
			if (m_label_current_sub)
				m_label_current_sub->setText( strip_simple_pango_markup( upd.description ) );
		}

		if (m_details_list && (!it->parent() || it->parent()->isOpen()))
			m_details_list->ensureItemVisible( it );
	}

	const int curr_op = m_worker->get_current_op();
	if ( curr_op != (int)m_curr_op )
	{
		m_curr_op = curr_op;
		const double frac = (m_operations.size() > 0) ? (1.0 / (double)m_operations.size()) : 1.0;
		TQString all_text = TQString::fromUtf8(
			Glib::ustring::compose( _("%1 of %2 operations completed"),
			                        m_curr_op, m_operations.size() ).c_str() );
		if (m_progress_all)
		{
			m_progress_all->set_text( all_text );
			m_progress_all->set_fraction( frac * (double)m_curr_op );
		}

		if (m_curr_op < (unsigned int)m_operations.size())
		{
			if (m_label_current)
				m_label_current->setText( strip_simple_pango_markup( m_operations[m_curr_op]->m_description ) );
			if (m_progress_current)
			{
				m_progress_current->set_fraction( 0 );
				m_progress_current->set_text( TQString::fromLatin1(" ") );
			}
			if (m_label_current_sub)
				m_label_current_sub->setText( "" );
		}
	}

	if ( !m_worker->running() && updates.empty() )
	{
		m_success = m_worker->get_success();
		on_worker_finished();
	}
}

void Dialog_Progress_TQt::on_save()
{
	const TQString filename = TQFileDialog::getSaveFileName(
		TQString::fromLatin1("tdeparted_details.htm"),
		TQString::fromLatin1("HTML (*.htm *.html)"),
		this,
		"save_details",
		TQString::fromUtf8( _("Save Details") ) );
	if (filename.isEmpty())
		return;
	std::ofstream out( filename.local8Bit().data() );
	if (!out)
	{
		TQMessageBox::critical( this, TQString::fromUtf8( _("Save Details") ), tr("Failed to open file for writing"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	out << "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>\n";
	out << "<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='" << Utils::get_lang() << "' lang='" << Utils::get_lang() << "'>\n";
	out << "<head><meta http-equiv='Content-Type' content='text/html;charset=utf-8' />\n";
	out << "<title>tdeParted Details</title>\n";
	out << "<style type='text/css'>table {border:0} th {text-align:left} .number_col {text-align:right}</style>\n";
	out << "</head><body>\n";

	std::vector<Glib::ustring> lines;
	Utils::split( GParted_Core::get_version_and_config_string(), lines, "\n" );
	out << "<pre style='font-family:monospace'>";
	out << "  __     __    ___  ___   ___  _____________ \n";
	out << " / /____/ /__ / _ \\/ _ | / _ \\/_  __/ __/ _ \\\n";
	out << "/ __/ _  / -_) ___/ __ |/ , _/ / / / _// // /\n";
	out << "\\__/\\_,_/\\__/_/  /_/ |_/_/|_| /_/ /___/____/ \n";
	out << "       -= TDE Partition Manager =-";
	out << "</pre>\n";
	for (unsigned int i = 1; i < lines.size(); i++)
		out << "<p>" << lines[i] << "</p>\n";

	for (unsigned int i = 0; i < m_devices.size(); i++)
	{
		out << "<p>_____________________________________________</p>\n";
		write_device_details_html_tqt( m_devices[i], out );
	}
	for (unsigned int i = 0; i < m_operations.size(); i++)
	{
		out << "<p>_____________________________________________</p>\n";
		write_operation_details_html_tqt( m_operations[i]->m_operation_detail, out );
	}
	out << "</body></html>";
	out.close();
	if (!out)
		TQMessageBox::critical( this, TQString::fromUtf8( _("Save Details") ), tr("Failed to write file"), TQMessageBox::Ok, TQMessageBox::NoButton );
}

void Dialog_Progress_TQt::closeEvent( TQCloseEvent *e )
{
	if (m_running)
		e->ignore();
	else
		TQDialog::closeEvent( e );
}

void Dialog_Progress_TQt::accept()
{
	if (m_running)
		return;
	TQDialog::accept();
}



static void init_icon_paths_once()
{
	static int done = 0;
	if (done)
		return;
	done = 1;

	TQMimeSourceFactory *f = TQMimeSourceFactory::defaultFactory();
	if (!f)
		return;

	/* Ensure common formats are registered for file lookup. */
	f->setExtensionType( TQString::fromLatin1("png"), "image/png" );
	f->setExtensionType( TQString::fromLatin1("xpm"), "image/x-xpixmap" );

	TQStringList paths = f->filePath();
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/24x24/actions");
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/22x22/actions");
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/16x16/actions");
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/24x24/apps");
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/22x22/apps");
	paths << TQString::fromLatin1("/usr/share/icons/Adwaita/16x16/apps");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/24x24/actions");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/22x22/actions");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/16x16/actions");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/24x24/apps");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/22x22/apps");
	paths << TQString::fromLatin1("/usr/share/icons/gnome/16x16/apps");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/24x24/actions");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/22x22/actions");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/16x16/actions");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/24x24/apps");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/22x22/apps");
	paths << TQString::fromLatin1("/usr/share/icons/hicolor/16x16/apps");
	paths << TQString::fromLatin1("/usr/share/pixmaps");
	paths << TQString::fromLatin1("data/icons");
	f->setFilePath( paths );
}

static int active_partitions_on_device_count_tqt( const Device &device )
{
	int active_count = 0;
	for (unsigned int k = 0; k < device.partitions.size(); k++)
	{
		if (device.partitions[k].busy && device.partitions[k].type != TYPE_UNALLOCATED)
			active_count++;
		if (device.partitions[k].busy && device.partitions[k].type == TYPE_EXTENDED)
		{
			for (unsigned int j = 0; j < device.partitions[k].logicals.size(); j++)
			{
				if (device.partitions[k].logicals[j].busy && device.partitions[k].logicals[j].type != TYPE_UNALLOCATED)
					active_count++;
			}
		}
	}
	return active_count;
}

class Dialog_Disklabel_TQt : public TQDialog
{
public:
	Dialog_Disklabel_TQt( const Device &device, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_combo( 0 ),
	  m_labeltypes()
	{
		setCaption( tr("Create Partition Table") );
		setModal( true );
		TQVBoxLayout *v = new TQVBoxLayout( this );
		v->setMargin( 8 );
		v->setSpacing( 6 );

		TQString warn = tr("WARNING: This will ERASE ALL DATA on the ENTIRE DISK %1")
			.arg( TQString::fromUtf8( device.get_path().c_str() ) );
		TQLabel *lbl_warn = new TQLabel( warn, this );
		v->addWidget( lbl_warn );

		TQHBoxLayout *h = new TQHBoxLayout();
		h->setSpacing( 6 );
		v->addLayout( h );
		h->addWidget( new TQLabel( tr("Select new partition table type:"), this ) );
		m_combo = new TQComboBox( false, this );
		h->addWidget( m_combo, 1 );

		m_labeltypes = GParted_Core::get_disklabeltypes();
		Glib::ustring default_label;
		if (device.length < 4LL * GIBIBYTE)
			default_label = "msdos";
		else
			default_label = "gpt";

		int active_index = 0;
		for (unsigned int t = 0; t < m_labeltypes.size(); t++)
		{
			m_combo->insertItem( TQString::fromUtf8( m_labeltypes[t].c_str() ) );
			if (m_labeltypes[t] == default_label)
				active_index = (int)t;
		}
		m_combo->setCurrentItem( active_index );

		TQHBoxLayout *hb = new TQHBoxLayout();
		hb->addStretch( 1 );
		TQPushButton *cancel = new TQPushButton( tr("Cancel"), this );
		TQPushButton *apply = new TQPushButton( tr("Apply"), this );
		hb->addWidget( cancel );
		hb->addWidget( apply );
		v->addLayout( hb );
		connect( cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		connect( apply, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );

		resize( 520, 180 );
	}

	Glib::ustring get_disklabel() const
	{
		if (!m_combo)
			return "";
		const int idx = m_combo->currentItem();
		if (idx < 0 || idx >= (int)m_labeltypes.size())
			return "";
		return m_labeltypes[idx];
	}

private:
	TQComboBox *m_combo;
	std::vector<Glib::ustring> m_labeltypes;
};

static TQPixmap make_fstype_color_pixmap( FSType fstype );
static bool apt_package_exists_tqt( const TQString &pkg );
static const char *fs_install_package_tqt( FSType fstype );

struct SmartInfo_TQt
{
	int is_nvme;
	int smart_passed;
	long temperature;
	long power_on_hours;
	long power_cycles;
	long percent_used;
	long media_errors;
	long critical_warning;
	long reallocated;
};

static int smart_find_smart_passed_tqt( const char *buf )
{
	const char *p = strstr( buf, "\"smart_status\"" );
	if (!p)
		return -1;

	p = strstr( p, "\"passed\"" );
	if (!p)
		return -1;

	p = strchr( p, ':' );
	if (!p)
		return -1;

	while (*p == ':' || *p == ' ')
		p++;

	if (!strncmp( p, "true", 4 ))
		return 1;
	if (!strncmp( p, "false", 5 ))
		return 0;
	return -1;
}

static long smart_find_long_tqt( const char *buf, const char *key )
{
	const char *p = strstr( buf, key );
	if (!p)
		return -1;

	p = strchr( p, ':' );
	if (!p)
		return -1;

	return strtol( p + 1, nullptr, 10 );
}

static long smart_find_ata_raw_tqt( const char *buf, int id )
{
	char pattern[32];
	snprintf( pattern, sizeof(pattern), "\"id\": %d", id );

	const char *p = strstr( buf, pattern );
	if (!p)
		return -1;

	p = strstr( p, "\"value\":" );
	if (!p)
		return -1;

	return strtol( p + 8, nullptr, 10 );
}

static long smart_find_temperature_current_tqt( const char *buf )
{
	const char *p = strstr( buf, "\"temperature\"" );
	if (!p)
		return -1;
	const char *q = strstr( p, "\"current\"" );
	if (!q)
		return -1;
	return smart_find_long_tqt( q, "\"current\"" );
}

static TQString smart_find_json_string_tqt( const char *buf, const char *key )
{
	const char *p = strstr( buf, key );
	if (!p)
		return TQString();
	p = strchr( p, ':' );
	if (!p)
		return TQString();
	p++;
	while (*p == ' ')
		p++;
	if (*p != '"')
		return TQString();
	p++;
	const char *e = strchr( p, '"' );
	if (!e)
		return TQString();
	return TQString::fromUtf8( std::string( p, (size_t)(e - p) ).c_str() );
}

static TQString smart_extract_smartctl_error_tqt( const char *buf )
{
	const char *p = strstr( buf, "\"smartctl\"" );
	if (!p)
		return TQString();
	p = strstr( p, "\"messages\"" );
	if (!p)
		return TQString();
	const char *end = strstr( p, "]" );
	if (!end)
		end = p + 8192;

	const char *m = p;
	while (m && m < end)
	{
		const char *sev = strstr( m, "\"severity\"" );
		if (!sev || sev >= end)
			break;
		const char *sevp = strstr( sev, "\"error\"" );
		if (sevp && sevp < end)
		{
			const char *sp = strstr( m, "\"string\"" );
			if (sp && sp < end)
				return smart_find_json_string_tqt( sp, "\"string\"" );
			break;
		}
		m = strstr( sev + 1, "{" );
	}
	return TQString();
}

static uint64_t timespec_to_ns_u64( const struct timespec &ts )
{
	return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

static double ns_to_seconds_d( uint64_t ns )
{
	return (double)ns / 1000000000.0;
}

static int pick_benchmark_mountpoint_tqt( const Device &d, uint64_t need_bytes, Glib::ustring &mountpoint )
{
	mountpoint.clear();
	Mount_Info::load_cache();
	for (unsigned int i = 0; i < d.partitions.size(); i++)
	{
		const Partition &p = d.partitions[i];
		const std::vector<Glib::ustring> &mps = p.get_mountpoints();
		if (mps.size() > 0 && !mps[0].empty())
		{
			struct statvfs sv;
			if (statvfs( mps[0].c_str(), &sv ) != 0)
				continue;
			if ((sv.f_flag & ST_RDONLY) != 0)
				continue;
			const uint64_t free_bytes = (uint64_t)sv.f_bavail * (uint64_t)sv.f_frsize;
			if (free_bytes < need_bytes)
				continue;
			mountpoint = mps[0];
			return 1;
		}
	}
	return 0;
}

static TQString format_mbs_tqt( double mbs )
{
	if (mbs < 0.0)
		mbs = 0.0;
	char b[64];
	snprintf( b, sizeof(b), "%.1f MB/s", mbs );
	return TQString::fromLatin1( b );
}

static int simple_benchmark_seq1m_tqt( const Glib::ustring &mountpoint,
	                                  uint64_t total_bytes,
	                                  uint32_t block_size,
	                                  TQProgressBar *pb,
	                                  TQLabel *phase,
	                                  double &out_write_mbs,
	                                  double &out_read_mbs,
	                                  TQString &out_error )
{
	out_write_mbs = 0.0;
	out_read_mbs = 0.0;
	out_error = TQString();
	if (!pb)
	{
		out_error = "Invalid progress bar";
		return 0;
	}
	if (mountpoint.empty())
	{
		out_error = "Missing mount point";
		return 0;
	}

	struct statvfs sv;
	if (statvfs( mountpoint.c_str(), &sv ) != 0)
	{
		out_error = "Could not query filesystem usage";
		return 0;
	}
	if ((sv.f_flag & ST_RDONLY) != 0)
	{
		out_error = "File system is read-only";
		return 0;
	}
	uint64_t free_bytes = (uint64_t)sv.f_bavail * (uint64_t)sv.f_frsize;
	if (free_bytes < total_bytes + (16ULL << 20))
	{
		out_error = "Not enough free space for benchmark";
		return 0;
	}

	char path[512];
	snprintf( path, sizeof(path), "%s/.tdeparted_bench_%ld.bin", mountpoint.c_str(), (long)getpid() );

	void *buf = nullptr;
	if (posix_memalign( &buf, 4096, block_size ) != 0)
	{
		out_error = "Could not allocate buffer";
		return 0;
	}
	memset( buf, 0xA5, block_size );

	const uint64_t blocks = (total_bytes + block_size - 1) / block_size;
	total_bytes = blocks * (uint64_t)block_size;

	const int passes = 3;
	const int total_steps = (int)(blocks * (uint64_t)passes * 2ULL);
	int step = 0;
	uint64_t ns_write_sum = 0;
	uint64_t ns_read_sum = 0;
	struct timespec t0, t1;

	pb->setProgress( 0, total_steps );
	for (int pass = 0; pass < passes; pass++)
	{
		int fd = open( path, O_CREAT | O_TRUNC | O_RDWR, 0600 );
		if (fd < 0)
		{
			free( buf );
			out_error = "Could not create benchmark file";
			return 0;
		}

		if (phase)
			phase->setText( TQObject::tr("Write") );
		clock_gettime( CLOCK_MONOTONIC_RAW, &t0 );
		for (uint64_t i = 0; i < blocks; i++, step++)
		{
			ssize_t wr = write( fd, buf, (size_t)block_size );
			if (wr != (ssize_t)block_size)
			{
				close( fd );
				unlink( path );
				free( buf );
				out_error = "Write failed";
				return 0;
			}
			if ((step & 0xF) == 0)
			{
				pb->setProgress( step, total_steps );
				tqApp->processEvents();
			}
		}
		fsync( fd );
		clock_gettime( CLOCK_MONOTONIC_RAW, &t1 );
		ns_write_sum += timespec_to_ns_u64( t1 ) - timespec_to_ns_u64( t0 );
		close( fd );

		fd = open( path, O_RDONLY | O_DIRECT );
		if (fd < 0)
			fd = open( path, O_RDONLY );
		if (fd < 0)
		{
			unlink( path );
			free( buf );
			out_error = "Could not reopen benchmark file";
			return 0;
		}
		(void)posix_fadvise( fd, 0, (off_t)total_bytes, POSIX_FADV_DONTNEED );
		(void)posix_fadvise( fd, 0, (off_t)total_bytes, POSIX_FADV_SEQUENTIAL );

		if (phase)
			phase->setText( TQObject::tr("Read") );
		clock_gettime( CLOCK_MONOTONIC_RAW, &t0 );
		for (uint64_t i = 0; i < blocks; i++, step++)
		{
			ssize_t rd = read( fd, buf, (size_t)block_size );
			if (rd != (ssize_t)block_size)
			{
				close( fd );
				unlink( path );
				free( buf );
				out_error = "Read failed";
				return 0;
			}
			if ((step & 0xF) == 0)
			{
				pb->setProgress( step, total_steps );
				tqApp->processEvents();
			}
		}
		clock_gettime( CLOCK_MONOTONIC_RAW, &t1 );
		ns_read_sum += timespec_to_ns_u64( t1 ) - timespec_to_ns_u64( t0 );
		close( fd );
	}

	pb->setProgress( total_steps, total_steps );
	tqApp->processEvents();

	const double bytes_total_all = (double)total_bytes * (double)passes;
	const double sec_write = ns_to_seconds_d( ns_write_sum );
	const double sec_read = ns_to_seconds_d( ns_read_sum );
	if (sec_write > 0.0)
		out_write_mbs = (bytes_total_all / (1024.0 * 1024.0)) / sec_write;
	if (sec_read > 0.0)
		out_read_mbs = (bytes_total_all / (1024.0 * 1024.0)) / sec_read;

	unlink( path );
	free( buf );
	return 1;
}

static void smart_parse_tqt( const char *buf, SmartInfo_TQt &s )
{
	memset( &s, 0, sizeof(s) );
	s.smart_passed = -1;

	if (strstr( buf, "\"nvme_smart_health_information_log\"" ))
	{
		s.is_nvme = 1;
		s.temperature      = smart_find_long_tqt( buf, "\"temperature\"" );
		s.power_on_hours   = smart_find_long_tqt( buf, "\"power_on_hours\"" );
		s.power_cycles     = smart_find_long_tqt( buf, "\"power_cycles\"" );
		s.percent_used     = smart_find_long_tqt( buf, "\"percentage_used\"" );
		s.media_errors     = smart_find_long_tqt( buf, "\"media_errors\"" );
		s.critical_warning = smart_find_long_tqt( buf, "\"critical_warning\"" );
	}
	else
	{
		s.is_nvme = 0;
		s.temperature    = smart_find_temperature_current_tqt( buf );
		s.power_on_hours = smart_find_ata_raw_tqt( buf, 9 );
		s.power_cycles   = smart_find_ata_raw_tqt( buf, 12 );
		s.reallocated    = smart_find_ata_raw_tqt( buf, 5 );
		s.smart_passed   = smart_find_smart_passed_tqt( buf );
	}
}

static TQString smart_format_report_tqt( const SmartInfo_TQt &s )
{
	TQString r;
	r += TQString::fromLatin1("Temperature      : ") + TQString::number( s.temperature ) + TQString::fromLatin1(" C\n");
	r += TQString::fromLatin1("Power-on hours   : ") + TQString::number( s.power_on_hours ) + TQString::fromLatin1("\n");
	r += TQString::fromLatin1("Power cycles     : ") + TQString::number( s.power_cycles ) + TQString::fromLatin1("\n");

	if (s.is_nvme)
	{
		r += TQString::fromLatin1("Wear level       : ") + TQString::number( s.percent_used ) + TQString::fromLatin1(" %\n");
		r += TQString::fromLatin1("Media errors     : ") + TQString::number( s.media_errors ) + TQString::fromLatin1("\n");
		if (s.critical_warning == 0)
			r += TQString::fromLatin1("Health           : OK\n");
		else
			r += TQString::fromLatin1("Health           : FAIL\n");
	}
	else
	{
		r += TQString::fromLatin1("Reallocated sect.: ") + TQString::number( s.reallocated ) + TQString::fromLatin1("\n");
		if (s.smart_passed == 1)
			r += TQString::fromLatin1("Health           : OK\n");
		else if (s.smart_passed == 0)
			r += TQString::fromLatin1("Health           : FAIL\n");
		else
			r += TQString::fromLatin1("Health           : UNKNOWN\n");
	}

	return r;
}

class FS_Feature_List_Item_TQt : public TQListViewItem
{
public:
	FS_Feature_List_Item_TQt( TQListView *parent )
	: TQListViewItem( parent )
	{
		for (int i = 0; i < 16; i++)
		{
			m_no_col[i] = false;
			m_yes_col[i] = false;
		}
		m_install_pkg = TQString();
	}

	void set_no_col( int col, bool v )
	{
		if (col >= 0 && col < 16)
			m_no_col[col] = v;
	}

	void set_yes_col( int col, bool v )
	{
		if (col >= 0 && col < 16)
			m_yes_col[col] = v;
	}

	void set_install_pkg( const TQString &pkg ) { m_install_pkg = pkg; }
	const TQString &install_pkg() const { return m_install_pkg; }

protected:
	void paintCell( TQPainter *p, const TQColorGroup &cg, int column, int width, int align )
	{
		if (column == 1 || column == 11)
		{
			TQFont f = p->font();
			f.setBold( true );
			p->setFont( f );
			TQListViewItem::paintCell( p, cg, column, width, align );
			return;
		}

		if (column >= 0 && column < 16 && m_no_col[column])
		{
			TQColorGroup cg2( cg );
			cg2.setColor( TQColorGroup::Base, TQColor( 0xC0, 0x00, 0x00 ) );
			cg2.setColor( TQColorGroup::Text, TQColor( 0xFF, 0xFF, 0xFF ) );
			cg2.setColor( TQColorGroup::Foreground, TQColor( 0xFF, 0xFF, 0xFF ) );
			TQListViewItem::paintCell( p, cg2, column, width, align );
			return;
		}
		if (column >= 0 && column < 16 && m_yes_col[column])
		{
			TQColorGroup cg2( cg );
			cg2.setColor( TQColorGroup::Base, TQColor( 0x3D, 0xAE, 0xE9 ) );
			cg2.setColor( TQColorGroup::Text, TQColor( 0x00, 0x00, 0x00 ) );
			cg2.setColor( TQColorGroup::Foreground, TQColor( 0x00, 0x00, 0x00 ) );
			TQListViewItem::paintCell( p, cg2, column, width, align );
			return;
		}
		TQListViewItem::paintCell( p, cg, column, width, align );
	}

private:
	bool m_no_col[16];
	bool m_yes_col[16];
	TQString m_install_pkg;
};

class FS_Feature_List_TQt : public TQListView
{
public:
	FS_Feature_List_TQt( TQWidget *parent )
	: TQListView( parent )
	{
	}

protected:
	void contentsMousePressEvent( TQMouseEvent *e )
	{
		TQListView::contentsMousePressEvent( e );
		if (!e)
			return;
		if (e->button() != TQt::LeftButton)
			return;

		const int install_col = 11;
		const int col = header() ? header()->sectionAt( e->pos().x() ) : -1;
		if (col != install_col)
			return;

		TQListViewItem *raw = itemAt( e->pos() );
		FS_Feature_List_Item_TQt *it = dynamic_cast<FS_Feature_List_Item_TQt *>( raw );
		if (!it)
			return;
		const TQString pkg = it->install_pkg();
		if (pkg.isEmpty())
			return;

		TQString msg = tr("A terminal will be launched to install the required software package:\n\n%1\n\nAfter installation, click 'Rescan For Supported Actions' to refresh this list.").arg( pkg );
		const int r = TQMessageBox::warning( this, tr("Install Required Software"), msg,
		                                    TQMessageBox::Ok, TQMessageBox::Cancel );
		if (r != TQMessageBox::Ok)
			return;
		if (!apt_package_exists_tqt( pkg ))
		{
			TQString emsg = tr("The package name could not be validated with apt-cache:\n\n%1\n\nPlease verify your APT sources and package name.").arg( pkg );
			TQMessageBox::critical( this, tr("Error"), emsg, TQMessageBox::Ok, TQMessageBox::NoButton );
			return;
		}

		const TQString cmd = TQString::fromLatin1("konsole -e bash -c \"sudo apt install -y ") + pkg + TQString::fromLatin1("\"");
		try
		{
			Glib::spawn_command_line_async( cmd.latin1() );
		}
		catch (...)
		{
			TQMessageBox::critical( this, tr("Error"), tr("Could not launch terminal for installation."), TQMessageBox::Ok, TQMessageBox::NoButton );
		}
	}
};

class Dialog_Features_TQt : public TQDialog
{
public:
	Dialog_Features_TQt( const std::vector<FS> &fss, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_list( 0 )
	{
		setCaption( tr("File System Support") );
		TQVBoxLayout *v = new TQVBoxLayout( this );
		v->setMargin( 6 );
		v->setSpacing( 4 );

		m_list = new FS_Feature_List_TQt( this );
		m_list->setRootIsDecorated( false );
		m_list->setAllColumnsShowFocus( true );
		m_list->addColumn( tr("Color") );
		m_list->addColumn( tr("File System") );
		m_list->addColumn( tr("Create") );
		m_list->addColumn( tr("Grow") );
		m_list->addColumn( tr("Shrink") );
		m_list->addColumn( tr("Move") );
		m_list->addColumn( tr("Copy") );
		m_list->addColumn( tr("Check") );
		m_list->addColumn( tr("Label") );
		m_list->addColumn( tr("UUID") );
		m_list->addColumn( tr("Required Software") );
		m_list->addColumn( tr("[Install]") );
		m_list->setColumnWidth( 0, 26 );
		m_list->setColumnWidth( 11, 70 );
		v->addWidget( m_list, 1 );

		TQString narrative = tr("This chart shows the actions supported on file systems.");
		narrative += TQString::fromLatin1("\n");
		narrative += tr("Not all actions are available on all file systems, in part due to the nature of file systems and limitations in the required software.");
		TQLabel *lbl_narrative = new TQLabel( narrative, this );
		lbl_narrative->setAlignment( TQt::AlignLeft | TQt::AlignTop | TQt::WordBreak );
		v->addWidget( lbl_narrative );

		TQHBoxLayout *hb = new TQHBoxLayout();
		hb->addStretch( 1 );
		m_btn_rescan = new TQPushButton( tr("Rescan For Supported Actions"), this );
		m_btn_close = new TQPushButton( tr("Close"), this );
		hb->addWidget( m_btn_rescan );
		hb->addWidget( m_btn_close );
		v->addLayout( hb );
		connect( m_btn_close, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		connect( m_btn_rescan, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );

		load_filesystems( fss );
		resize( 940, 520 );
	}

	void load_filesystems( const std::vector<FS> &fss )
	{
		if (!m_list)
			return;
		m_list->clear();
		for (unsigned int i = 0; i < fss.size(); i++)
		{
			if (!GParted_Core::supported_filesystem( fss[i].fstype ))
				continue;
			add_one( fss[i] );
		}
		for (unsigned int i = 0; i < fss.size(); i++)
		{
			if (fss[i].fstype == FS_OTHER)
			{
				add_one( fss[i] );
				break;
			}
		}
	}

	bool rescan_requested() const { return result() == TQDialog::Accepted; }

private:
	void add_one( const FS &fs )
	{
		FS_Feature_List_Item_TQt *it = new FS_Feature_List_Item_TQt( m_list );
		it->setPixmap( 0, make_fstype_color_pixmap( fs.fstype ) );
		it->setText( 1, TQString::fromUtf8( Utils::get_filesystem_string( fs.fstype ).c_str() ) );
		it->setText( 2, fs.create             ? tr("Yes") : tr("No") );
		it->setText( 3, fs.grow               ? tr("Yes") : tr("No") );
		it->setText( 4, fs.shrink             ? tr("Yes") : tr("No") );
		it->setText( 5, fs.move               ? tr("Yes") : tr("No") );
		it->setText( 6, fs.copy               ? tr("Yes") : tr("No") );
		it->setText( 7, fs.check              ? tr("Yes") : tr("No") );
		it->setText( 8, fs.write_label        ? tr("Yes") : tr("No") );
		it->setText( 9, fs.write_uuid         ? tr("Yes") : tr("No") );
		it->setText( 10, TQString::fromUtf8( Utils::get_filesystem_software( fs.fstype ).c_str() ) );
		it->setText( 11, TQString() );

		it->set_no_col( 2, !fs.create );
		it->set_no_col( 3, !fs.grow );
		it->set_no_col( 4, !fs.shrink );
		it->set_no_col( 5, !fs.move );
		it->set_no_col( 6, !fs.copy );
		it->set_no_col( 7, !fs.check );
		it->set_no_col( 8, !fs.write_label );
		it->set_no_col( 9, !fs.write_uuid );

		it->set_yes_col( 2, fs.create );
		it->set_yes_col( 3, fs.grow );
		it->set_yes_col( 4, fs.shrink );
		it->set_yes_col( 5, fs.move );
		it->set_yes_col( 6, fs.copy );
		it->set_yes_col( 7, fs.check );
		it->set_yes_col( 8, fs.write_label );
		it->set_yes_col( 9, fs.write_uuid );

		if (!fs.create)
		{
			const char *pkg = fs_install_package_tqt( fs.fstype );
			if (pkg && pkg[0])
			{
				const TQString tpkg = TQString::fromLatin1( pkg );
				if (apt_package_exists_tqt( tpkg ))
				{
					it->setText( 11, tr("[Install]") );
					it->set_install_pkg( tpkg );
				}
			}
		}
	}

	TQListView *m_list;
	TQPushButton *m_btn_rescan;
	TQPushButton *m_btn_close;
};

static bool open_encrypted_partition_tqt( const Partition &partition, const char *entered_password, Glib::ustring &message )
{
	const char *pw = nullptr;
	if (entered_password == nullptr)
	{
		pw = PasswordRAMStore::lookup( partition.uuid );
		if (pw == nullptr)
		{
			message = "";
			return false;
		}
	}
	else
	{
		pw = entered_password;
	}

	const Glib::ustring mapping_name = Utils::generate_encryption_mapping_name( partition.get_path() );
	Glib::ustring cmd = "cryptsetup luksOpen " +
	                    Glib::shell_quote( partition.get_path() ) + " " +
	                    Glib::shell_quote( mapping_name );
	Glib::ustring output;
	Glib::ustring error;
	bool success = ! Utils::execute_command( cmd, pw, output, error );
	if (success && pw != nullptr)
		PasswordRAMStore::store( partition.uuid, pw );
	else if (!success)
		PasswordRAMStore::erase( partition.uuid );

	message = (success) ? "" : "Failed to open LUKS encryption";
	if (!success)
		message += "\n\n# " + cmd + "\n" + error;
	return success;
}

class Dialog_Text_Entry_TQt : public TQDialog
{
public:
	Dialog_Text_Entry_TQt( const TQString &title, const TQString &label, const TQString &text, int max_len, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_edit( 0 )
	{
		setCaption( title );
		TQVBoxLayout *v = new TQVBoxLayout( this );
		TQLabel *l = new TQLabel( label, this );
		v->addWidget( l );
		m_edit = new TQLineEdit( this );
		m_edit->setText( text );
		m_edit->setValidator( new TQRegExpValidator( TQRegExp( "[^/\\\\\\x00-\\x1f]*" ), m_edit ) );
		if (max_len > 0)
			m_edit->setMaxLength( max_len );
		v->addWidget( m_edit );
		TQHBoxLayout *h = new TQHBoxLayout();
		TQPushButton *ok = new TQPushButton( tr("OK"), this );
		TQPushButton *cancel = new TQPushButton( tr("Cancel"), this );
		h->addStretch( 1 );
		h->addWidget( ok );
		h->addWidget( cancel );
		v->addLayout( h );
		connect( ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		m_edit->setFocus();
		resize( 420, 120 );
	}

	TQString get_text() const
	{
		if (!m_edit)
			return TQString();
		return m_edit->text();
	}

private:
	TQLineEdit *m_edit;
};

class Dialog_Type_Confirm_TQt : public TQDialog
{
public:
	Dialog_Type_Confirm_TQt( const TQString &title, const TQString &label, const TQString &expected, TQWidget *parent )
		: TQDialog( parent, 0, true )
		, m_expected( expected )
		, m_edit( 0 )
		, m_error( 0 )
	{
		setCaption( title );
		setMinimumWidth( 520 );

		TQVBoxLayout *vb = new TQVBoxLayout( this );
		vb->setMargin( 10 );
		vb->setSpacing( 8 );
		TQLabel *l = new TQLabel( label, this );
		l->setTextFormat( TQt::PlainText );
		l->setAlignment( TQt::AlignLeft | TQt::AlignTop | TQt::WordBreak );
		vb->addWidget( l );
		m_edit = new TQLineEdit( this );
		m_edit->setText( TQString() );
		m_edit->setValidator( new TQRegExpValidator( TQRegExp( "[^\\x00-\\x1f]*" ), m_edit ) );
		vb->addWidget( m_edit );
		m_error = new TQLabel( TQString(), this );
		m_error->setTextFormat( TQt::PlainText );
		m_error->setAlignment( TQt::AlignLeft | TQt::AlignTop | TQt::WordBreak );
		vb->addWidget( m_error );

		TQHBoxLayout *hb = new TQHBoxLayout();
		TQPushButton *ok = new TQPushButton( tr("Proceed"), this );
		TQPushButton *cancel = new TQPushButton( tr("Cancel"), this );
		hb->addStretch( 1 );
		hb->addWidget( ok );
		hb->addWidget( cancel );
		vb->addLayout( hb );
		connect( ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		m_edit->setFocus();
	}

	bool matches() const
	{
		if (!m_edit)
			return false;
		return m_edit->text().stripWhiteSpace() == m_expected;
	}

	void show_mismatch_error()
	{
		if (m_error)
			m_error->setText( tr("Confirmation text does not match.") );
	}

private:
	TQString m_expected;
	TQLineEdit *m_edit;
	TQLabel *m_error;
};

static bool destructive_type_confirm_tqt( TQWidget *parent, const TQString &title, const TQString &target_path, const TQString &warning_text )
{
	TQString msg = warning_text;
	msg += TQString::fromLatin1("\n\n");
	msg += Win_GParted_TQt::tr("Target: %1").arg( target_path );
	const int r1 = TQMessageBox::warning( parent, title, msg, Win_GParted_TQt::tr("Continue"), Win_GParted_TQt::tr("Cancel") );
	if (r1 != 0)
		return false;

	TQString label = Win_GParted_TQt::tr("Type the target path to confirm:\n%1").arg( target_path );
	while (1)
	{
		Dialog_Type_Confirm_TQt dlg( title, label, target_path, parent );
		if (dlg.exec() != TQDialog::Accepted)
			return false;
		if (dlg.matches())
			return true;
		dlg.show_mismatch_error();
	}
}

class Dialog_Password_Entry_TQt : public TQDialog
{
public:
	Dialog_Password_Entry_TQt( const TQString &title, const TQString &label, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_edit( 0 ),
	  m_error( 0 )
	{
		setCaption( title );
		TQVBoxLayout *v = new TQVBoxLayout( this );
		TQLabel *l = new TQLabel( label, this );
		v->addWidget( l );
		m_edit = new TQLineEdit( this );
		m_edit->setEchoMode( TQLineEdit::Password );
		v->addWidget( m_edit );
		m_error = new TQLabel( TQString(), this );
		m_error->setTextFormat( TQt::RichText );
		m_error->hide();
		v->addWidget( m_error );
		TQHBoxLayout *h = new TQHBoxLayout();
		TQPushButton *ok = new TQPushButton( tr("OK"), this );
		TQPushButton *cancel = new TQPushButton( tr("Cancel"), this );
		h->addStretch( 1 );
		h->addWidget( ok );
		h->addWidget( cancel );
		v->addLayout( h );
		connect( ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		m_edit->setFocus();
		resize( 420, 160 );
	}

	const char * get_password_cstr() const
	{
		m_pw_bytes = m_edit ? m_edit->text().utf8() : TQCString();
		return m_pw_bytes.data();
	}

	void set_error_message( const Glib::ustring &msg )
	{
		if (!m_error)
			return;
		if (msg.empty())
		{
			m_error->hide();
			m_error->setText( TQString() );
			return;
		}
		m_error->setText( TQString::fromUtf8( msg.c_str() ) );
		m_error->show();
	}

	~Dialog_Password_Entry_TQt() override
	{
		// Zero out password memory to prevent leakage from freed heap.
		if (m_pw_bytes.data() && m_pw_bytes.length() > 0)
			memset( m_pw_bytes.data(), 0, m_pw_bytes.length() );
	}

private:
	mutable TQCString m_pw_bytes;
	TQLineEdit *m_edit;
	TQLabel *m_error;
};

class Dialog_Manage_Flags_TQt : public TQDialog
{
public:
	Dialog_Manage_Flags_TQt( const Partition &partition,
	                         std::map<Glib::ustring, bool> flag_info,
	                         GParted_Core &core,
	                         TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_partition( partition ),
	  m_flag_info( flag_info ),
	  m_core( core ),
	  m_changed( false ),
	  m_list( 0 ),
	  m_warning( 0 )
	{
		setCaption( TQString::fromUtf8( Glib::ustring::compose( "Manage flags on %1", partition.get_path() ).c_str() ) );
		TQVBoxLayout *v = new TQVBoxLayout( this );
		m_list = new TQListView( this );
		m_list->addColumn( TQString() );
		m_list->setRootIsDecorated( false );
		m_list->setAllColumnsShowFocus( true );
		v->addWidget( m_list );

		m_warning = new TQLabel( TQString(), this );
		m_warning->setTextFormat( TQt::RichText );
		v->addWidget( m_warning );

		TQHBoxLayout *h = new TQHBoxLayout();
		TQPushButton *close = new TQPushButton( tr("Close"), this );
		h->addStretch( 1 );
		h->addWidget( close );
		v->addLayout( h );
		connect( close, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( m_list, TQT_SIGNAL(clicked(TQListViewItem*)), this, TQT_SLOT(on_item_clicked(TQListViewItem*)) );

		reload();
		resize( 420, 320 );
	}

	bool changed() const { return m_changed; }

private slots:
	void on_item_clicked( TQListViewItem *item )
	{
		if (!item)
			return;
		TQCheckListItem *c = dynamic_cast<TQCheckListItem*>( item );
		if (!c)
			return;

		const Glib::ustring flag = c->text(0).utf8().data();
		const bool new_state = c->isOn();
		m_core.toggle_flag( m_partition, flag, new_state );
		m_flag_info = m_core.get_available_flags( m_partition );
		m_changed = true;
		reload();
	}

private:
	void reload()
	{
		if (!m_list)
			return;
		m_list->clear();
		for (std::map<Glib::ustring, bool>::const_iterator it = m_flag_info.begin(); it != m_flag_info.end(); ++it)
		{
			TQCheckListItem *ci = new TQCheckListItem( m_list, TQString::fromUtf8( it->first.c_str() ), TQCheckListItem::CheckBox );
			ci->setOn( it->second );
		}
		update_warning();
	}

	void update_warning()
	{
		if (!m_warning)
			return;
		bool esp_flag = false;
		std::map<Glib::ustring, bool>::const_iterator it = m_flag_info.find( "esp" );
		if (it != m_flag_info.end())
			esp_flag = it->second;
		Glib::ustring warning = GParted_Core::check_logical_esp_warning( m_partition.type, esp_flag );
		m_warning->setText( TQString::fromUtf8( warning.c_str() ) );
		m_warning->setShown( warning.size() > 0 );
	}

	const Partition &m_partition;
	std::map<Glib::ustring, bool> m_flag_info;
	GParted_Core &m_core;
	bool m_changed;
	TQListView *m_list;
	TQLabel *m_warning;
};

void Win_GParted_TQt::action_name_partition()
{
	if (!m_selected_partition)
		return;
	const int max_len = m_devices[m_current_device].get_max_partition_name_length();
	Dialog_Text_Entry_TQt dlg( tr("Name Partition"),
	                          TQString::fromUtf8( Glib::ustring::compose( "Set a new name for %1", m_selected_partition->get_path() ).c_str() ),
	                          TQString::fromUtf8( m_selected_partition->name.c_str() ),
	                          max_len,
	                          this );
	if (dlg.exec() != TQDialog::Accepted)
		return;
	const Glib::ustring new_name = dlg.get_text().utf8().data();
	if (new_name == m_selected_partition->name)
		return;

	Partition *part_temp = m_selected_partition->clone();
	part_temp->name = new_name;
	std::unique_ptr<Operation> op( new OperationNamePartition( m_devices[m_current_device], *m_selected_partition, *part_temp ) );
	delete part_temp;
	part_temp = 0;
	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	refresh_visual();
	update_valid_actions();
}


void Win_GParted_TQt::action_manage_flags()
{
	if (!m_selected_partition)
		return;
	this->setCursor( TQCursor( TQt::WaitCursor ) );
	if (tqApp)
		tqApp->processEvents();
	std::map<Glib::ustring, bool> flag_info = m_core.get_available_flags( *m_selected_partition );
	Dialog_Manage_Flags_TQt dlg( *m_selected_partition, flag_info, m_core, this );
	this->unsetCursor();
	dlg.exec();
	if (dlg.changed())
		menu_device_refresh_devices();
}

static bool ensure_device_unused_tqt( TQWidget *parent, const Device &d, const TQString &title );

void Win_GParted_TQt::menu_device_load_disk_image()
{
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Load Disk Image"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	TQString filename = TQFileDialog::getOpenFileName( TQString(), TQString::fromLatin1("Images (*.img *.raw *.bin *.iso *.qcow2 *.qcow *.vmdk);;All Files (*)"), this, "open_disk_image_virtual", tr("Load Disk Image") );
	if (filename.isEmpty())
		return;
	const Glib::ustring img_path( filename.local8Bit().data() );
	const bool ro_ext = virtual_attach_is_ro_by_ext_tqt( img_path );
	const bool writable = virtual_image_is_writable_tqt( img_path );
	const bool ro = ro_ext || !writable;

	Glib::ustring lower;
	lower.reserve( img_path.size() );
	for (unsigned int i = 0; i < img_path.size(); i++)
		lower += (char)g_ascii_tolower( (gchar)img_path[i] );
	const bool want_nbd = (lower.rfind(".qcow2") == (lower.size() - 6)) ||
	                      (lower.rfind(".qcow")  == (lower.size() - 5)) ||
	                      (lower.rfind(".vmdk")  == (lower.size() - 5));

	Glib::ustring dev_path;
	Glib::ustring err;
	int backend = VBACKEND_LOOP;
	bool ok;
	if (want_nbd)
	{
		backend = VBACKEND_NBD;
		ok = virtual_attach_nbd_tqt( img_path, ro, dev_path, err );
	}
	else
	{
		backend = VBACKEND_LOOP;
		ok = virtual_attach_loop_tqt( img_path, ro, dev_path, err );
	}
	if (!ok)
	{
		TQMessageBox::critical( this, tr("Load Disk Image"), tr("Failed to attach image") + TQString::fromLatin1("\n\n") + TQString::fromUtf8( err.c_str() ), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	VirtualAttach_TQt va;
	va.dev_path = dev_path;
	va.image_path = img_path;
	va.backend = backend;
	bool already = false;
	for (unsigned int i = 0; i < m_virtual_attaches.size(); i++)
	{
		if (m_virtual_attaches[i].dev_path == dev_path)
		{
			already = true;
			break;
		}
	}
	if (!already)
		m_virtual_attaches.push_back( va );

	menu_device_refresh_devices();
	for (unsigned int i = 0; i < m_devices.size(); i++)
	{
		if (m_devices[i].get_path() == dev_path)
		{
			m_combo_devices->setCurrentItem( (int)i );
			combo_devices_changed( (int)i );
			break;
		}
	}
}

void Win_GParted_TQt::menu_device_detach_virtual_device()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Detach Virtual Device"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	const Glib::ustring dev_path = m_devices[m_current_device].get_path();
	int idx = -1;
	for (unsigned int i = 0; i < m_virtual_attaches.size(); i++)
	{
		if (m_virtual_attaches[i].dev_path == dev_path)
		{
			idx = (int)i;
			break;
		}
	}
	if (idx < 0)
		return;
	if (!ensure_device_unused_tqt( this, m_devices[m_current_device], tr("Detach Virtual Device") ))
		return;

	Glib::ustring err;
	if (!virtual_detach_tqt( dev_path, m_virtual_attaches[idx].backend, err ))
	{
		TQMessageBox::critical( this, tr("Detach Virtual Device"), tr("Failed to detach virtual device") + TQString::fromLatin1("\n\n") + TQString::fromUtf8( err.c_str() ), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	m_virtual_attaches.erase( m_virtual_attaches.begin() + idx );
	menu_device_refresh_devices();
}

void Win_GParted_TQt::menu_device_smart_infos()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	const Glib::ustring dev_path = m_devices[m_current_device].get_path();
	if (dev_path.empty())
		return;

	const Glib::ustring cmd = "smartctl -a -j " + Glib::shell_quote( dev_path );
	std::string out;
	std::string err;
	int status = -1;
	try
	{
		Glib::spawn_command_line_sync( cmd.raw(), &out, &err, &status );
	}
	catch (...)
	{
		TQMessageBox::critical( this, tr("Error"), tr("Failed to execute smartctl."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (status != 0 || out.empty())
	{
		TQString em = (!out.empty()) ? smart_extract_smartctl_error_tqt( out.c_str() ) : TQString();
		TQString m;
		if (!em.isEmpty())
			m = tr("Error") + TQString::fromLatin1(": ") + em;
		else
			m = tr("smartctl returned an error.");
		TQMessageBox::critical( this, tr("SMART infos"), m, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	SmartInfo_TQt si;
	smart_parse_tqt( out.c_str(), si );
	const TQString model = smart_find_json_string_tqt( out.c_str(), "\"model_name\"" );
	const TQString serial = smart_find_json_string_tqt( out.c_str(), "\"serial_number\"" );
	TQString report = smart_format_report_tqt( si );

	TQDialog dlg( this, 0, true );
	dlg.setCaption( tr("SMART infos") );
	TQVBoxLayout *v = new TQVBoxLayout( &dlg );
	v->setMargin( 8 );
	v->setSpacing( 6 );
	TQString title = tr("Device:");
	title += TQString::fromLatin1(" ") + TQString::fromUtf8( dev_path.c_str() );
	TQLabel *lbl_title = new TQLabel( title, &dlg );
	TQFont f = lbl_title->font();
	f.setBold( true );
	lbl_title->setFont( f );
	v->addWidget( lbl_title );
	{
		TQString full;
		if (!model.isEmpty())
			full += model;
		if (!serial.isEmpty())
		{
			if (!full.isEmpty())
				full += TQString::fromLatin1("  ");
			full += tr("Serial:") + TQString::fromLatin1(" ") + serial;
		}
		if (!full.isEmpty())
			v->addWidget( new TQLabel( full, &dlg ) );
	}
	{
		TQFrame *sep = new TQFrame( &dlg );
		sep->setFrameShape( TQFrame::HLine );
		sep->setFrameShadow( TQFrame::Sunken );
		v->addWidget( sep );
	}
	{
		TQGridLayout *g = new TQGridLayout( 0, 2, 6 );
		g->setColStretch( 1, 1 );
		int row = 0;
		TQLabel *l1 = new TQLabel( tr("Temperature"), &dlg );
		TQLabel *v1 = new TQLabel( TQString::number( si.temperature ) + TQString::fromLatin1(" C"), &dlg );
		g->addWidget( l1, row, 0 );
		g->addWidget( v1, row, 1 );
		row++;
		TQLabel *l2 = new TQLabel( tr("Power-on hours"), &dlg );
		TQLabel *v2 = new TQLabel( TQString::number( si.power_on_hours ), &dlg );
		g->addWidget( l2, row, 0 );
		g->addWidget( v2, row, 1 );
		row++;
		TQLabel *l3 = new TQLabel( tr("Power cycles"), &dlg );
		TQLabel *v3 = new TQLabel( TQString::number( si.power_cycles ), &dlg );
		g->addWidget( l3, row, 0 );
		g->addWidget( v3, row, 1 );
		row++;
		if (si.is_nvme)
		{
			TQLabel *l4 = new TQLabel( tr("Wear level"), &dlg );
			TQLabel *v4 = new TQLabel( TQString::number( si.percent_used ) + TQString::fromLatin1(" %"), &dlg );
			g->addWidget( l4, row, 0 );
			g->addWidget( v4, row, 1 );
			row++;
			TQLabel *l5 = new TQLabel( tr("Media errors"), &dlg );
			TQLabel *v5 = new TQLabel( TQString::number( si.media_errors ), &dlg );
			g->addWidget( l5, row, 0 );
			g->addWidget( v5, row, 1 );
			row++;
			TQLabel *l6 = new TQLabel( tr("Health"), &dlg );
			TQLabel *v6 = new TQLabel( (si.critical_warning == 0) ? tr("OK") : tr("FAIL"), &dlg );
			g->addWidget( l6, row, 0 );
			g->addWidget( v6, row, 1 );
			row++;
		}
		else
		{
			TQLabel *l4 = new TQLabel( tr("Reallocated sect."), &dlg );
			TQLabel *v4 = new TQLabel( TQString::number( si.reallocated ), &dlg );
			g->addWidget( l4, row, 0 );
			g->addWidget( v4, row, 1 );
			row++;
			TQLabel *l5 = new TQLabel( tr("Health"), &dlg );
			TQString hv = (si.smart_passed == 1) ? tr("OK") : ((si.smart_passed == 0) ? tr("FAIL") : tr("UNKNOWN"));
			TQLabel *v5 = new TQLabel( hv, &dlg );
			g->addWidget( l5, row, 0 );
			g->addWidget( v5, row, 1 );
			row++;
		}
		v->addLayout( g, 1 );
		(void)report;
	}
	TQHBoxLayout *hb = new TQHBoxLayout();
	hb->addStretch( 1 );
	TQPushButton *btn_close = new TQPushButton( tr("Close"), &dlg );
	hb->addWidget( btn_close );
	v->addLayout( hb );
	TQObject::connect( btn_close, TQT_SIGNAL(clicked()), &dlg, TQT_SLOT(accept()) );
	dlg.resize( 520, 340 );
	dlg.exec();
}

void Win_GParted_TQt::action_label_filesystem()
{
	if (!m_selected_partition)
		return;
	const Partition &filesystem_ptn = m_selected_partition->get_filesystem_partition();
	Dialog_Text_Entry_TQt dlg( tr("Label File System"),
	                          TQString::fromUtf8( Glib::ustring::compose( "Set a new file system label on %1", filesystem_ptn.get_path() ).c_str() ),
	                          TQString::fromUtf8( filesystem_ptn.get_filesystem_label().c_str() ),
	                          0,
	                          this );
	if (dlg.exec() != TQDialog::Accepted)
		return;
	const Glib::ustring new_label = dlg.get_text().utf8().data();
	if (new_label == filesystem_ptn.get_filesystem_label())
		return;

	Partition *part_temp = m_selected_partition->clone();
	part_temp->get_filesystem_partition().set_filesystem_label( new_label );
	std::unique_ptr<Operation> op( new OperationLabelFileSystem( m_devices[m_current_device], *m_selected_partition, *part_temp ) );
	delete part_temp;
	part_temp = 0;
	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_check()
{
	if (!m_selected_partition)
		return;

	std::unique_ptr<Operation> operation( new OperationCheck( m_devices[m_current_device], *m_selected_partition ) );
	if (!add_operation( m_devices[m_current_device], std::move(operation) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_change_uuid()
{
	if (!m_selected_partition)
		return;

	const Partition &filesystem_ptn = m_selected_partition->get_filesystem_partition();
	const FileSystem *filesystem_object = m_core.get_filesystem_object( filesystem_ptn.fstype );
	if (filesystem_object && filesystem_object->get_custom_text( CTEXT_CHANGE_UUID_WARNING ) != "")
	{
		TQString msg = TQString::fromUtf8( filesystem_object->get_custom_text( CTEXT_CHANGE_UUID_WARNING, 0 ).c_str() );
		TQString sec;
		for (int i = 1; filesystem_object->get_custom_text( CTEXT_CHANGE_UUID_WARNING, i ) != ""; i++)
		{
			if (i > 1)
				sec += "\n\n";
			sec += TQString::fromUtf8( filesystem_object->get_custom_text( CTEXT_CHANGE_UUID_WARNING, i ).c_str() );
		}
		TQMessageBox::warning( this, tr("Warning"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	}

	Partition *temp_ptn = m_selected_partition->clone();
	{
		Partition &temp_filesystem_ptn = temp_ptn->get_filesystem_partition();
		if (temp_filesystem_ptn.fstype == FS_NTFS)
			temp_filesystem_ptn.uuid = UUID_RANDOM_NTFS_HALF;
		else
			temp_filesystem_ptn.uuid = UUID_RANDOM;
	}

	std::unique_ptr<Operation> operation( new OperationChangeUUID( m_devices[m_current_device], *m_selected_partition, *temp_ptn ) );
	delete temp_ptn;
	temp_ptn = 0;

	if (!add_operation( m_devices[m_current_device], std::move(operation) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	refresh_visual();
	update_valid_actions();
}

static int partition_in_operation_queue_count_tqt( const OperationVector &ops, const Partition &partition )
{
	 int count = 0;
	 const Glib::ustring path = partition.get_path();
	 for (unsigned int i = 0; i < ops.size(); i++)
	 {
	 	 if (ops[i]->m_type == OPERATION_DELETE)
	 	 {
	 	 	 if (ops[i]->get_partition_original().get_path() == path)
	 	 	 	 count++;
	 	 }
	 	 else
	 	 {
	 	 	 if (ops[i]->get_partition_original().get_path() == path ||
	 	 	     ops[i]->get_partition_new().get_path() == path)
	 	 	 	 count++;
	 	 }
	 }
	 return count;
}

static bool check_toggle_busy_allowed_tqt( TQWidget *parent, const OperationVector &ops, const Partition &partition, const Glib::ustring &disallowed_msg )
{
	 const int op_count = partition_in_operation_queue_count_tqt( ops, partition );
	 if (op_count <= 0)
	 	 return true;

	 TQString primary;
	 primary.sprintf( "%d operations are currently pending for partition %s", op_count, partition.get_path().c_str() );
	 TQString sec = TQString::fromUtf8( disallowed_msg.c_str() ) +
	 	 TQString::fromLatin1("\n") +
	 	 TQString::fromLatin1("Use the Edit menu to undo, clear or apply pending operations.");
	 TQMessageBox::information( parent, TQString::fromLatin1("Information"), primary + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	 return false;
}

static bool unmount_partition_tqt( const Partition &partition, Glib::ustring &error )
{
	 const std::vector<Glib::ustring>& fs_mountpoints = partition.get_mountpoints();
	 const std::vector<Glib::ustring> all_mountpoints = Mount_Info::get_all_mountpoints();
	 std::vector<Glib::ustring> skipped_mountpoints;
	 std::vector<Glib::ustring> umount_errors;

	 for (unsigned int i = 0; i < fs_mountpoints.size(); i++)
	 {
	 	 if (std::count( all_mountpoints.begin(), all_mountpoints.end(), fs_mountpoints[i] ) >= 2)
	 	 {
	 	 	 skipped_mountpoints.push_back( fs_mountpoints[i] );
	 	 }
	 	 else
	 	 {
	 	 	 Mount_Info::load_cache();
	 	 	 if (Mount_Info::is_dev_mounted_at( partition.get_path(), fs_mountpoints[i] ))
	 	 	 {
	 	 	 	 Glib::ustring cmd = "umount -v " + Glib::shell_quote( fs_mountpoints[i] );
	 	 	 	 Glib::ustring dummy;
	 	 	 	 Glib::ustring umount_error;
	 	 	 	 if (Utils::execute_command( cmd, dummy, umount_error ))
	 	 	 	 	 umount_errors.push_back( "# " + cmd + "\n" + umount_error );
	 	 	 }
	 	 }
	 }

	 if (umount_errors.size() > 0)
	 {
	 	 error = "<i>";
	 	 for (unsigned int i = 0; i < umount_errors.size(); i++)
	 	 {
	 	 	 if (i)
	 	 	 	 error += "</i>\n<i>";
	 	 	 error += umount_errors[i];
	 	 }
	 	 error += "</i>";
	 	 return false;
	 }
	 if (skipped_mountpoints.size() > 0)
	 {
	 	 error = "The partition could not be unmounted from the following mount points:";
	 	 error += "\n\n<i>";
	 	 for (unsigned int i = 0; i < skipped_mountpoints.size(); i++)
	 	 {
	 	 	 if (i)
	 	 	 	 error += "\n";
	 	 	 error += skipped_mountpoints[i];
	 	 }
	 	 error += "</i>\n\n";
	 	 error += "This is because other partitions are also mounted on these mount points.  You are advised to unmount them manually.";
	 	 return false;
	 }
	 return true;
}

static Glib::ustring username_for_media_mount_tqt()
{
	const char *u = getenv( "USER" );
	if (u && u[0])
		return Glib::ustring( u );
	struct passwd *pw = getpwuid( getuid() );
	if (pw && pw->pw_name && pw->pw_name[0])
		return Glib::ustring( pw->pw_name );
	return Glib::ustring();
}

static bool mount_partition_auto_tqt( const Partition &partition, Glib::ustring &error, Glib::ustring &mounted_on )
{
	mounted_on.clear();
	const Partition &filesystem_ptn = partition.get_filesystem_partition();
	if (filesystem_ptn.get_path().empty())
	{
		error = "Invalid device path";
		return false;
	}
	if (filesystem_ptn.fstype == FS_UNALLOCATED)
	{
		error = "Cannot mount unallocated space";
		return false;
	}

	Glib::ustring mountpoint;
	const std::vector<Glib::ustring> mps = filesystem_ptn.get_mountpoints();
	if (!mps.empty())
	{
		mountpoint = mps[0];
	}
	else
	{
		const Glib::ustring user = username_for_media_mount_tqt();
		Glib::ustring devname;
		{
			const Glib::ustring path = filesystem_ptn.get_path();
			const Glib::ustring::size_type slash = path.rfind( '/' );
			devname = (slash == Glib::ustring::npos) ? path : path.substr( slash + 1 );
		}
		if (user.empty())
			mountpoint = "/media/" + devname;
		else
			mountpoint = "/media/" + user + "/" + devname;
	}

	Glib::ustring cmd;
	Glib::ustring output;
	Glib::ustring err;
	Glib::ustring error_msg;
	bool success;

	cmd = "mkdir -p " + Glib::shell_quote( mountpoint );
	success = !Utils::execute_command( cmd, output, err );
	if (!success)
	{
		error = "# " + cmd + "\n" + err;
		return false;
	}

	cmd = "mount -v " + Glib::shell_quote( filesystem_ptn.get_path() ) + " " + Glib::shell_quote( mountpoint );
	success = !Utils::execute_command( cmd, output, err );
	if (!success)
	{
		error_msg = "# " + cmd + "\n" + err;
		const Glib::ustring type = Utils::get_filesystem_kernel_name( filesystem_ptn.fstype );
		if (!type.empty())
		{
			cmd = "mount -v -t " + Glib::shell_quote( type ) + " " + Glib::shell_quote( filesystem_ptn.get_path() ) + " " + Glib::shell_quote( mountpoint );
			success = !Utils::execute_command( cmd, output, err );
			if (!success)
				error_msg += "\n# " + cmd + "\n" + err;
		}
	}

	if (!success)
	{
		error = error_msg;
		return false;
	}

	mounted_on = mountpoint;
	return true;
}

static bool ensure_partition_unused_tqt( TQWidget *parent, const Partition &p, const TQString &title )
{
	if (p.type == TYPE_UNALLOCATED)
		return true;
	if (p.busy)
	{
		TQString msg = TQString::fromUtf8( Glib::ustring::compose( "Partition %1 is currently in use", p.get_path() ).c_str() );
		TQString sec = TQString::fromLatin1( "Unmount the file system or deactivate swap/volume group before continuing." );
		TQMessageBox::information( parent, title, msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return false;
	}
	Mount_Info::load_cache();
	if (Mount_Info::is_dev_mounted( p.get_path() ))
	{
		TQString msg = TQString::fromUtf8( Glib::ustring::compose( "Partition %1 is mounted or active", p.get_path() ).c_str() );
		TQString sec = TQString::fromLatin1( "Unmount the file system or deactivate swap before continuing." );
		TQMessageBox::information( parent, title, msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return false;
	}
	return true;
}

static bool ensure_device_unused_tqt( TQWidget *parent, const Device &d, const TQString &title )
{
	const int active_count = active_partitions_on_device_count_tqt( d );
	if (active_count > 0)
	{
		TQString msg = TQObject::tr("%1 partition(s) are currently active on device %2")
			.arg( TQString::number( active_count ) )
			.arg( TQString::fromUtf8( d.get_path().c_str() ) );
		TQString sec = TQObject::tr("Unmount file systems or deactivate swap/volume groups before continuing.");
		TQMessageBox::information( parent, title, msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return false;
	}
	return true;
}

void Win_GParted_TQt::action_toggle_crypt_busy_state()
{
	if (!m_selected_partition)
		return;

	enum Action
	{
		NONE      = 0,
		LUKSCLOSE = 1,
		LUKSOPEN  = 2
	};
	Action action = NONE;
	Glib::ustring disallowed_msg;
	Glib::ustring pulse_msg;
	Glib::ustring failure_msg;
	if (m_selected_partition->busy)
	{
		action = LUKSCLOSE;
		disallowed_msg = "The close encryption action cannot be performed when there are operations pending for the partition.";
		pulse_msg = Glib::ustring::compose( "Closing encryption on %1", m_selected_partition->get_path() );
		failure_msg = "Could not close encryption";
	}
	else
	{
		action = LUKSOPEN;
		disallowed_msg = "The open encryption action cannot be performed when there are operations pending for the partition.";
	}

	if (!check_toggle_busy_allowed_tqt( this, m_operations, *m_selected_partition, disallowed_msg ))
		return;

	bool success = false;
	Glib::ustring cmd;
	Glib::ustring output;
	Glib::ustring error;
	Glib::ustring error_msg;
	statusBar()->message( TQString::fromUtf8( pulse_msg.c_str() ) );
	
	switch (action)
	{
		case LUKSCLOSE:
			cmd = "cryptsetup luksClose " + Glib::shell_quote( m_selected_partition->get_mountpoint() );
			success = !Utils::execute_command( cmd, output, error );
			error_msg = "# " + cmd + "\n" + error;
			break;
		case LUKSOPEN:
		{
			success = open_encrypted_partition_tqt( *m_selected_partition, nullptr, error_msg );
			if (success)
				break;

			Dialog_Password_Entry_TQt dlg(
				tr("Open Encryption"),
				TQString::fromUtf8( Glib::ustring::compose( "Enter LUKS passphrase to open %1", m_selected_partition->get_path() ).c_str() ),
				this );
			do
			{
				if (dlg.exec() != TQDialog::Accepted)
					return;
				success = open_encrypted_partition_tqt( *m_selected_partition, dlg.get_password_cstr(), error_msg );
				dlg.set_error_message( error_msg );
			} while (!success);
		}
		break;
		default:
			break;
	}

	if (!success)
	{
		TQString t = TQString::fromUtf8( failure_msg.c_str() );
		TQString sec = TQString::fromUtf8( error_msg.c_str() );
		TQMessageBox::critical( this, tr("Error"), t + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	}

	menu_device_refresh_devices();
}

void Win_GParted_TQt::action_toggle_fs_busy_state()
{
	 if (!m_selected_partition)
	 	 return;
	 const Partition &filesystem_ptn = m_selected_partition->get_filesystem_partition();

	 enum Action
	 {
	 	 NONE = 0,
	 	 SWAPOFF = 1,
	 	 SWAPON = 2,
	 	 DEACTIVATE_VG = 3,
	 	 ACTIVATE_VG = 4,
	 	 UNMOUNT = 5,
	 	 MOUNT = 6
	 };
	 Action action = NONE;
	 Glib::ustring disallowed_msg;
	 Glib::ustring pulse_msg;
	 Glib::ustring failure_msg;

	 if (filesystem_ptn.fstype == FS_LINUX_SWAP && filesystem_ptn.busy)
	 {
	 	 action = SWAPOFF;
	 	 disallowed_msg = "The swapoff action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Deactivating swap on %1", filesystem_ptn.get_path() );
	 	 failure_msg = "Could not deactivate swap";
	 }
	 else if (filesystem_ptn.fstype == FS_LINUX_SWAP && !filesystem_ptn.busy)
	 {
	 	 action = SWAPON;
	 	 disallowed_msg = "The swapon action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Activating swap on %1", filesystem_ptn.get_path() );
	 	 failure_msg = "Could not activate swap";
	 }
	 else if (filesystem_ptn.fstype == FS_LVM2_PV && filesystem_ptn.busy)
	 {
	 	 action = DEACTIVATE_VG;
	 	 disallowed_msg = "The deactivate Volume Group action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Deactivating Volume Group %1", filesystem_ptn.get_mountpoint() );
	 	 failure_msg = "Could not deactivate Volume Group";
	 }
	 else if (filesystem_ptn.fstype == FS_LVM2_PV && !filesystem_ptn.busy)
	 {
	 	 action = ACTIVATE_VG;
	 	 disallowed_msg = "The activate Volume Group action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Activating Volume Group %1", filesystem_ptn.get_mountpoint() );
	 	 failure_msg = "Could not activate Volume Group";
	 }
	 else if (filesystem_ptn.busy)
	 {
	 	 action = UNMOUNT;
	 	 disallowed_msg = "The unmount action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Unmounting %1", filesystem_ptn.get_path() );
	 	 failure_msg = Glib::ustring::compose( "Could not unmount %1", filesystem_ptn.get_path() );
	 }
	 else
	 {
	 	 action = MOUNT;
	 	 disallowed_msg = "The mount action cannot be performed when there are operations pending for the partition.";
	 	 pulse_msg = Glib::ustring::compose( "Mounting %1", filesystem_ptn.get_path() );
	 	 failure_msg = Glib::ustring::compose( "Could not mount %1", filesystem_ptn.get_path() );
	 }

	 if (!check_toggle_busy_allowed_tqt( this, m_operations, *m_selected_partition, disallowed_msg ))
	 	 return;

	 statusBar()->message( TQString::fromUtf8( pulse_msg.c_str() ) );
	 bool success = false;
	 Glib::ustring cmd;
	 Glib::ustring output;
	 Glib::ustring error;
	 Glib::ustring error_msg;
	 switch (action)
	 {
	 	 case SWAPOFF:
	 	 	 cmd = "swapoff -v " + Glib::shell_quote( filesystem_ptn.get_path() );
	 	 	 success = !Utils::execute_command( cmd, output, error );
	 	 	 error_msg = "# " + cmd + "\n" + error;
	 	 	 break;
	 	 case SWAPON:
	 	 	 cmd = "swapon -v " + Glib::shell_quote( filesystem_ptn.get_path() );
	 	 	 success = !Utils::execute_command( cmd, output, error );
	 	 	 error_msg = "# " + cmd + "\n" + error;
	 	 	 break;
	 	 case DEACTIVATE_VG:
	 	 	 cmd = "lvm vgchange -a n " + Glib::shell_quote( filesystem_ptn.get_mountpoint() );
	 	 	 success = !Utils::execute_command( cmd, output, error );
	 	 	 error_msg = "# " + cmd + "\n" + error;
	 	 	 break;
	 	 case ACTIVATE_VG:
	 	 	 cmd = "lvm vgchange -a y " + Glib::shell_quote( filesystem_ptn.get_mountpoint() );
	 	 	 success = !Utils::execute_command( cmd, output, error );
	 	 	 error_msg = "# " + cmd + "\n" + error;
	 	 	 break;
	 	 case UNMOUNT:
	 	 	 success = unmount_partition_tqt( filesystem_ptn, error_msg );
	 	 	 break;
	 	 case MOUNT:
	 	 {
	 	 	 Glib::ustring mounted_on;
	 	 	 success = mount_partition_auto_tqt( *m_selected_partition, error_msg, mounted_on );
	 	 }
	 	 	 break;
	 	 default:
	 	 	 break;
	 }

	 if (!success)
	 {
	 	 TQString t = TQString::fromUtf8( failure_msg.c_str() );
	 	 TQString sec = TQString::fromUtf8( error_msg.c_str() );
	 	 TQMessageBox::critical( this, tr("Error"), t + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	 }

	 menu_device_refresh_devices();
}

void Win_GParted_TQt::menu_partition_mount_on( int id )
{
	 if (!m_selected_partition)
	 	 return;
	 int idx = -1;
	 for (unsigned int i = 0; i < m_menu_partition_mount_on_ids.size(); i++)
	 {
	 	 if (m_menu_partition_mount_on_ids[i] == id)
	 	 {
	 	 	 idx = (int)i;
	 	 	 break;
	 	 }
	 }
	 if (idx < 0 || idx >= (int)m_menu_partition_mount_on_mountpoints.size())
	 	 return;

	 Glib::ustring disallowed_msg = "The mount action cannot be performed when an operation is pending for the partition.";
	 if (!check_toggle_busy_allowed_tqt( this, m_operations, *m_selected_partition, disallowed_msg ))
	 	 return;

	 const Partition &filesystem_ptn = m_selected_partition->get_filesystem_partition();
	 const Glib::ustring mountpoint = m_menu_partition_mount_on_mountpoints[(unsigned int)idx];
	 statusBar()->message( TQString::fromUtf8( Glib::ustring::compose( "mounting %1 on %2", filesystem_ptn.get_path(), mountpoint ).c_str() ) );

	 Glib::ustring cmd;
	 Glib::ustring output;
	 Glib::ustring error;
	 Glib::ustring error_msg;
	 bool success;

	 cmd = "mount -v " + Glib::shell_quote( filesystem_ptn.get_path() ) + " " + Glib::shell_quote( mountpoint );
	 success = !Utils::execute_command( cmd, output, error );
	 if (!success)
	 {
	 	 error_msg = "# " + cmd + "\n" + error;
	 	 const Glib::ustring type = Utils::get_filesystem_kernel_name( filesystem_ptn.fstype );
	 	 if (!type.empty())
	 	 {
	 	 	 cmd = "mount -v -t " + Glib::shell_quote( type ) + " " + Glib::shell_quote( filesystem_ptn.get_path() ) + " " + Glib::shell_quote( mountpoint );
	 	 	 success = !Utils::execute_command( cmd, output, error );
	 	 	 if (!success)
	 	 	 	 error_msg += "\n# " + cmd + "\n" + error;
	 	 }
	 }

	 if (!success)
	 {
	 	 TQString fail = tr("Could not mount");
	 	 TQString sec = TQString::fromUtf8( error_msg.c_str() );
	 	 TQMessageBox::critical( this, tr("Error"), fail + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	 }

	 menu_device_refresh_devices();
}

static TQPixmap load_icon_by_name( const char *name )
{
	if (!name || !name[0])
		return TQPixmap();

	if (TDEGlobal::instance() && TDEGlobal::iconLoader())
	{
		const TQString iname = TQString::fromLatin1( name );
		TQPixmap pm = TDEGlobal::iconLoader()->loadIcon(
			iname,
			TDEIcon::MainToolbar,
			32,
			(int)TDEIcon::DefaultState,
			0,
			true );
		if (!pm.isNull())
			return pm;

		pm = TDEGlobal::iconLoader()->loadIcon(
			iname,
			TDEIcon::Toolbar,
			22,
			(int)TDEIcon::DefaultState,
			0,
			true );
		if (!pm.isNull())
			return pm;

		pm = TDEGlobal::iconLoader()->loadIcon(
			iname,
			TDEIcon::Small,
			16,
			(int)TDEIcon::DefaultState,
			0,
			true );
		if (!pm.isNull())
			return pm;
	}

	init_icon_paths_once();
	TQMimeSourceFactory *f = TQMimeSourceFactory::defaultFactory();
	if (!f)
		return TQPixmap();

	const TQString base = TQString::fromLatin1( name );
	const TQString try_names[2] = {
		base + TQString::fromLatin1(".png"),
		base + TQString::fromLatin1(".xpm")
	};

	const TQStringList paths = f->filePath();
	for (TQStringList::ConstIterator it = paths.begin(); it != paths.end(); ++it)
	{
		const TQString dir = *it;
		for (unsigned int i = 0; i < 2; i++)
		{
			TQString full = dir;
			if (!full.isEmpty() && full[full.length() - 1] != '/')
				full += '/';
			full += try_names[i];
			TQPixmap pm;
			if (pm.load( full ))
				return pm;
		}
	}

	return TQPixmap();
}

static TQPixmap make_fstype_color_pixmap( FSType fstype )
{
	TQPixmap pm( 16, 16 );
	pm.fill( TQt::white );
	const Glib::ustring hex = Utils::get_color( fstype );
	TQColor c( TQString::fromLatin1( hex.c_str() ) );
	TQPainter p( &pm );
	p.fillRect( 0, 0, 16, 16, c );
	p.end();
	return pm;
}

static bool apt_package_exists_tqt( const TQString &pkg )
{
	if (pkg.isEmpty())
		return false;

	std::string out;
	std::string err;
	int status = -1;
	try
	{
		const std::string cmd = std::string("apt-cache show ") + std::string( pkg.latin1() );
		Glib::spawn_command_line_sync( cmd, &out, &err, &status );
	}
	catch (...)
	{
		return false;
	}
	return status == 0;
}

static const char *fs_install_package_tqt( FSType fstype )
{
	switch (fstype)
	{
		case FS_BCACHEFS:   return "bcache-tools";
		case FS_BTRFS:      return "btrfs-progs";
		case FS_EXFAT:      return "exfatprogs";
		case FS_EXT2:
		case FS_EXT3:
		case FS_EXT4:       return "e2fsprogs";
		case FS_F2FS:       return "f2fs-tools";
		case FS_FAT16:
		case FS_FAT32:      return "dosfstools";
		case FS_HFS:
		case FS_HFSPLUS:    return "hfsprogs";
		case FS_JFS:        return "jfsutils";
		case FS_MINIX:      return "util-linux";
		case FS_NILFS2:     return "nilfs-tools";
		case FS_NTFS:       return "ntfs-3g";
		case FS_REISERFS:   return "reiserfsprogs";
		case FS_REISER4:    return "reiser4progs";
		case FS_UDF:        return "udftools";
		case FS_XFS:        return "xfsprogs";
		default:            return nullptr;
	}
}

static TQPixmap get_admin_pixmap()
{
	static int done = 0;
	static TQPixmap pm;
	if (!done)
	{
		done = 1;
		pm = load_icon_by_name( "dialog-password" );
		if (pm.isNull())
			pm = load_icon_by_name( "dialog-authentication" );
		if (pm.isNull())
			pm = load_icon_by_name( "gtk-dialog-authentication" );
		if (pm.isNull())
			pm = load_icon_by_name( "emblem-readonly" );
	}
	return pm;
}

static TQPixmap get_warning_pixmap()
{
	static int done = 0;
	static TQPixmap pm;
	if (!done)
	{
		done = 1;
		pm = load_icon_by_name( "dialog-warning" );
		if (pm.isNull())
			pm = load_icon_by_name( "gtk-dialog-warning" );
		if (pm.isNull())
			pm = load_icon_by_name( "dialog-error" );
		if (pm.isNull())
			pm = load_icon_by_name( "gtk-dialog-error" );
	}
	return pm;
}

class VisualDiskWidget : public TQWidget
{
public:
	VisualDiskWidget( Win_GParted_TQt *owner, TQWidget *parent )
	: TQWidget( parent ),
	  m_owner( owner ),
	  m_device_length( 0 ),
	  m_tot_sep( 0 ),
	  m_min_size( 0 ),
	  m_color_used( TQString::fromUtf8( Utils::get_color( FS_USED ).c_str() ) ),
	  m_color_unused( TQString::fromUtf8( Utils::get_color( FS_UNUSED ).c_str() ) ),
	  m_color_unallocated( TQString::fromUtf8( Utils::get_color( FS_UNALLOCATED ).c_str() ) ),
	  m_color_text( "black" )
	{
		setWFlags( getWFlags() | WNoAutoErase );
		setBackgroundMode( NoBackground );
		setSizePolicy( TQSizePolicy::Expanding, TQSizePolicy::Fixed );
		setFixedHeight( HEIGHT );
		setMouseTracking( true );
	}

	void load_partitions( const PartitionVector &partitions, Sector device_length )
	{
		clear();
		m_device_length = device_length;
		m_tot_sep = get_total_separator_px( partitions );
		set_static_data( partitions, m_visual_partitions, device_length );
		recalc();
		update();
	}

	void clear()
	{
		m_visual_partitions.clear();
		m_device_length = 0;
		m_tot_sep = 0;
		m_min_size = 0;
		m_selected_partition = 0;
		update();
	}

	void set_selected( const Partition *p )
	{
		m_selected_partition = p;
		update();
	}

protected:
	void resizeEvent( TQResizeEvent * )
	{
		recalc();
		m_backing = TQPixmap();
	}

	void paintEvent( TQPaintEvent * )
	{
		if (m_backing.isNull() || m_backing.width() != width() || m_backing.height() != height())
			m_backing = TQPixmap( width(), height() );

		{
			TQPainter p( &m_backing );
			p.fillRect( rect(), colorGroup().base() );
			draw_partitions( p, m_visual_partitions );
			if (m_selected_partition)
				draw_selection_rect( p, m_visual_partitions );
		}

		bitBlt( this, 0, 0, &m_backing );
	}

	void mousePressEvent( TQMouseEvent *e )
	{
		if (!e)
			return;

		const int x = e->x();
		const int y = e->y();
		const Partition *p = 0;
		find_partition_by_coord( m_visual_partitions, x, y, p );
		if (p)
		{
			m_selected_partition = p;
			update();
			if (m_owner)
				m_owner->select_partition_from_visualdisk( p );
		}

		if (e->button() == Qt::RightButton)
		{
			if (m_owner)
				m_owner->popup_partition_menu_at_cursor();
		}
	}

	void mouseDoubleClickEvent( TQMouseEvent *e )
	{
		if (!e)
			return;
		if (e->button() != Qt::LeftButton)
			return;
		if (m_owner)
			m_owner->visualdisk_activate_information();
	}

private:
	enum { MAIN_BORDER = 5, BORDER = 4, SEP = 4, HEIGHT = 70 + 2 * MAIN_BORDER };

	struct VisualPartition
	{
		double fraction;
		int x_start, length;
		int y_start, height;
		int x_used_start, used_length;
		int x_unused_start, unused_length;
		int x_unallocated_start, unallocated_length;
		int y_usage_start, usage_height;
		int x_text, y_text;
		TQColor color;
		TQString text;
		const Partition *partition_ptr;
		std::vector<VisualPartition> logicals;
		VisualPartition()
		{
			fraction = 0.0;
			x_start = length = 0;
			y_start = height = 0;
			x_used_start = used_length = 0;
			x_unused_start = unused_length = 0;
			x_unallocated_start = unallocated_length = 0;
			y_usage_start = usage_height = 0;
			x_text = y_text = 0;
			partition_ptr = 0;
		}
	};

	static int get_total_separator_px( const PartitionVector &partitions )
	{
		for ( unsigned int t = 0; t < partitions.size(); t++ )
			if (partitions[t].type == TYPE_EXTENDED)
				return ( (int)partitions[t].logicals.size() - 1 + (int)partitions.size() - 1 ) * SEP;
		return ( (int)partitions.size() - 1 ) * SEP;
	}

	static void set_static_data( const PartitionVector &partitions,
	                            std::vector<VisualPartition> &visual_partitions,
	                            Sector device_length )
	{
		for ( unsigned int t = 0; t < partitions.size(); t++ )
		{
			visual_partitions.push_back( VisualPartition() );
			VisualPartition &vp = visual_partitions.back();
			vp.partition_ptr = &partitions[t];
			const Sector ptn_len = partitions[t].get_sector_length();
			vp.fraction = ptn_len / (double)device_length;
			{
				const Glib::ustring c = Utils::get_color( partitions[t].get_filesystem_partition().fstype );
				vp.color = TQColor( TQString::fromUtf8( c.c_str() ) );
			}

			if (partitions[t].type == TYPE_EXTENDED)
				set_static_data( partitions[t].logicals, vp.logicals, ptn_len );
			else
				vp.text = TQString::fromUtf8( (partitions[t].get_path() + "\n" +
					Utils::format_size( ptn_len, partitions[t].sector_size )).c_str() );
		}
	}

	static int calc_length( std::vector<VisualPartition> &visual_partitions, int length_px, int min_size )
	{
		int calced_length = 0;
		for ( int t = 0; t < (int)visual_partitions.size(); t++ )
		{
			VisualPartition &vp = visual_partitions[t];
			vp.length = Utils::round( length_px * vp.fraction );
			if (vp.logicals.size() > 0)
				vp.length = calc_length( vp.logicals, vp.length - (2 * BORDER), min_size ) + (2 * BORDER);
			else if (vp.length < min_size)
				vp.length = min_size;
			calced_length += vp.length;
		}
		return calced_length + ((int)visual_partitions.size() - 1) * SEP;
	}

	static void calc_position_and_height( std::vector<VisualPartition> &visual_partitions, int start, int border )
	{
		for ( unsigned int t = 0; t < visual_partitions.size(); t++ )
		{
			VisualPartition &vp = visual_partitions[t];
			vp.x_start = start;
			vp.y_start = border;
			vp.height = HEIGHT - (border * 2);
			if (vp.logicals.size() > 0)
				calc_position_and_height( vp.logicals, vp.x_start + BORDER, vp.y_start + BORDER );
			start += vp.length + SEP;
		}
	}

	static void calc_usage( std::vector<VisualPartition> &visual_partitions )
	{
		for ( unsigned int t = 0; t < visual_partitions.size(); t++ )
		{
			VisualPartition &vp = visual_partitions[t];
			if (vp.partition_ptr &&
			    vp.partition_ptr->fstype != FS_UNALLOCATED &&
			    vp.partition_ptr->type != TYPE_EXTENDED)
			{
				if (vp.partition_ptr->sector_usage_known())
				{
					vp.partition_ptr->get_usage_triple( vp.length - BORDER * 2,
					                             vp.used_length,
					                             vp.unused_length,
					                             vp.unallocated_length );

					if (!vp.text.isEmpty() && vp.partition_ptr->get_sector_length() > 0)
					{
						const Sector used = vp.partition_ptr->get_sectors_used();
						if (used >= 0)
						{
							const Sector total = vp.partition_ptr->get_sector_length();
							const unsigned long long u = (unsigned long long)used;
							const unsigned long long tot = (unsigned long long)total;
							const unsigned long long pct = (tot > 0) ? ((u * 100ULL + (tot / 2ULL)) / tot) : 0ULL;
							int nl = vp.text.find( '\n' );
							if (nl >= 0)
							{
								TQString first = vp.text.left( nl );
								TQString second = vp.text.mid( nl + 1 );
								const int used_pos = second.find( TQString::fromLatin1(" (Used:") );
								if (used_pos >= 0)
									second = second.left( used_pos );
								second += TQString::fromLatin1(" (Used: ");
								second += TQString::number( (unsigned long)pct );
								second += TQString::fromLatin1(" %)");
								vp.text = first + TQString::fromLatin1("\n") + second;
							}
						}
					}
				}
				else
				{
					vp.used_length = 0;
					vp.unused_length = vp.length - BORDER * 2;
					vp.unallocated_length = 0;
				}

				vp.x_used_start = vp.x_start + BORDER;
				vp.x_unused_start = vp.x_used_start + vp.used_length;
				vp.x_unallocated_start = vp.x_unused_start + vp.unused_length;
				vp.y_usage_start = vp.y_start + BORDER;
				vp.usage_height = vp.height - (2 * BORDER);
			}

			if (vp.logicals.size() > 0)
				calc_usage( vp.logicals );
		}
	}

	static void calc_text( std::vector<VisualPartition> &visual_partitions, const TQFontMetrics &fm )
	{
		for ( unsigned int t = 0; t < visual_partitions.size(); t++ )
		{
			VisualPartition &vp = visual_partitions[t];
			vp.x_text = vp.y_text = 0;
			if (!vp.text.isEmpty())
			{
				const TQRect br = fm.boundingRect( 0, 0, 4096, 4096,
								  TQt::AlignLeft | TQt::AlignTop, vp.text );
				const int length = br.width();
				const int height = br.height();
				if (length < vp.length - (2 * BORDER) - 2)
				{
					vp.x_text = vp.x_start + Utils::round( (vp.length / 2) - (length / 2) );
					vp.y_text = vp.y_start + Utils::round( (vp.height / 2) - (height / 2) );
				}
			}
			if (vp.logicals.size() > 0)
				calc_text( vp.logicals, fm );
		}
	}

	static int spreadout_leftover_px( std::vector<VisualPartition> &visual_partitions, int pixels )
	{
		int extended = -1;
		for ( unsigned int t = 0; t < visual_partitions.size() && pixels > 0; t++ )
			if (!visual_partitions[t].logicals.size())
			{
				visual_partitions[t].length++;
				pixels--;
			}
			else
				extended = (int)t;

		if (extended > -1 && pixels > 0)
		{
			const int actually_used = pixels - spreadout_leftover_px( visual_partitions[extended].logicals, pixels );
			visual_partitions[extended].length += actually_used;
			pixels -= actually_used;
		}
		return pixels;
	}

	void recalc()
	{
		m_min_size = BORDER * 2 + 2;
		const int available_size = width() - (2 * MAIN_BORDER);
		int calced = 0;
		int px_left;
		do
		{
			px_left = available_size - m_tot_sep;
			calced = available_size;
			do
			{
				px_left -= (calced - available_size);
				calced = calc_length( m_visual_partitions, px_left, m_min_size );
			}
			while (calced > available_size && px_left > 0);
			m_min_size--;
		}
		while (px_left <= 0 && m_min_size > 0);

		if (m_visual_partitions.size() && calced > 0)
		{
			px_left = available_size - calced;
			while (px_left > 0)
				px_left = spreadout_leftover_px( m_visual_partitions, px_left );
		}

		calc_position_and_height( m_visual_partitions, MAIN_BORDER, MAIN_BORDER );
		calc_usage( m_visual_partitions );
		calc_text( m_visual_partitions, TQFontMetrics( font() ) );
	}

	void draw_partition( TQPainter &p, const VisualPartition &vp )
	{
		const TQPixmap &pm_part = get_gradient_pixmap( vp.color );
		p.drawPixmap( TQRect( vp.x_start, vp.y_start, vp.length, vp.height ), pm_part );
		if (vp.used_length > 0)
		{
			const TQPixmap &pm_used = get_gradient_pixmap( m_color_used );
			p.drawPixmap( TQRect( vp.x_used_start, vp.y_usage_start, vp.used_length, vp.usage_height ), pm_used );
		}
		if (vp.unused_length > 0)
		{
			const TQPixmap &pm_unused = get_gradient_pixmap( m_color_unused );
			p.drawPixmap( TQRect( vp.x_unused_start, vp.y_usage_start, vp.unused_length, vp.usage_height ), pm_unused );
		}
		if (vp.unallocated_length > 0)
		{
			const TQPixmap &pm_unalloc = get_gradient_pixmap( m_color_unallocated );
			p.drawPixmap( TQRect( vp.x_unallocated_start, vp.y_usage_start, vp.unallocated_length, vp.usage_height ), pm_unalloc );
		}

		if (vp.x_text > 0)
		{
			const TQFont old_font = p.font();
			TQFont f = old_font;
			f.setBold( true );
			p.setFont( f );
			p.setPen( m_color_text );
			p.drawText( vp.x_text, vp.y_text, 4096, 4096, TQt::AlignLeft | TQt::AlignTop, vp.text );
			p.setFont( old_font );
		}
	}

	void draw_partitions( TQPainter &p, const std::vector<VisualPartition> &visual_partitions )
	{
		for ( unsigned int t = 0; t < visual_partitions.size(); t++ )
		{
			draw_partition( p, visual_partitions[t] );
			if (visual_partitions[t].logicals.size() > 0)
				draw_partitions( p, visual_partitions[t].logicals );
		}
	}

	static bool find_partition_by_coord( const std::vector<VisualPartition> &visual_partitions,
	                                   int x,
	                                   int y,
	                                   const Partition *&out )
	{
		for (unsigned int i = 0; i < visual_partitions.size(); i++)
		{
			const VisualPartition &vp = visual_partitions[i];
			if (vp.logicals.size() > 0)
				if (find_partition_by_coord( vp.logicals, x, y, out ))
					return true;
			if (vp.x_start <= x && x < vp.x_start + vp.length && vp.y_start <= y && y < vp.y_start + vp.height)
			{
				out = vp.partition_ptr;
				return true;
			}
		}
		return false;
	}

	void draw_selection_rect( TQPainter &p, const std::vector<VisualPartition> &visual_partitions )
	{
		const VisualPartition *vp = find_visual_partition_by_ptn( visual_partitions, m_selected_partition );
		if (!vp)
			return;
		TQPen pen( m_color_used );
		pen.setWidth( 2 );
		pen.setStyle( TQt::DashLine );
		p.setPen( pen );
		p.setBrush( TQt::NoBrush );
		p.drawRect( vp->x_start + BORDER/2, vp->y_start + BORDER/2, vp->length - BORDER, vp->height - BORDER );
	}

	static const VisualPartition *find_visual_partition_by_ptn( const std::vector<VisualPartition> &visual_partitions,
	                                                         const Partition *p )
	{
		if (!p)
			return 0;
		for (unsigned int i = 0; i < visual_partitions.size(); i++)
		{
			const VisualPartition &vp = visual_partitions[i];
			if (vp.logicals.size() > 0)
			{
				const VisualPartition *r = find_visual_partition_by_ptn( vp.logicals, p );
				if (r)
					return r;
			}
			if (vp.partition_ptr && *vp.partition_ptr == *p)
				return &vp;
		}
		return 0;
	}

	Win_GParted_TQt *m_owner;
	Sector m_device_length;
	std::vector<VisualPartition> m_visual_partitions;
	int m_tot_sep;
	int m_min_size;
	const TQColor m_color_used;
	const TQColor m_color_unused;
	const TQColor m_color_unallocated;
	const TQColor m_color_text;
	const Partition *m_selected_partition;
	TQPixmap m_backing;
	mutable std::vector< std::pair< unsigned int, TQPixmap > > m_gradient_cache;

	static inline unsigned int rgb_key( const TQColor &c )
	{
		return (unsigned int)c.rgb();
	}

	static inline int clamp_u8( int v )
	{
		return (v < 0) ? 0 : ((v > 255) ? 255 : v);
	}

	static inline TQColor lighten_color( const TQColor &c, int amount )
	{
		return TQColor( clamp_u8( c.red() + ((255 - c.red()) * amount) / 255 ),
		               clamp_u8( c.green() + ((255 - c.green()) * amount) / 255 ),
		               clamp_u8( c.blue() + ((255 - c.blue()) * amount) / 255 ) );
	}

	static inline TQColor darken_color( const TQColor &c, int amount )
	{
		return TQColor( clamp_u8( c.red() - (c.red() * amount) / 255 ),
		               clamp_u8( c.green() - (c.green() * amount) / 255 ),
		               clamp_u8( c.blue() - (c.blue() * amount) / 255 ) );
	}

	static TQPixmap make_gradient_pixmap( const TQColor &base )
	{
		enum { W = 16, H = 64 };
		TQImage img( W, H, 32 );
		img.setAlphaBuffer( false );
		const TQColor c0 = base;
		const TQColor c1 = darken_color( base, 96 );
		for ( int y = 0; y < H; y++ )
		{
			const int dist = (y <= (H / 2)) ? y : (H - 1 - y);
			const int denom = (H / 2);
			const int t = (denom > 0) ? (dist * 255) / denom : 0;
			const int inv = 255 - t;
			const int r = (c0.red() * t + c1.red() * inv) / 255;
			const int g = (c0.green() * t + c1.green() * inv) / 255;
			const int b = (c0.blue() * t + c1.blue() * inv) / 255;
			const unsigned int px = 0xFF000000u | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;
			for ( int x = 0; x < W; x++ )
				img.setPixel( x, y, px );
		}
		TQPixmap pm;
		pm.convertFromImage( img );
		return pm;
	}

	const TQPixmap &get_gradient_pixmap( const TQColor &c ) const
	{
		const unsigned int key = rgb_key( c );
		for ( unsigned int i = 0; i < m_gradient_cache.size(); i++ )
			if (m_gradient_cache[i].first == key)
				return m_gradient_cache[i].second;
		m_gradient_cache.push_back( std::make_pair( key, make_gradient_pixmap( c ) ) );
		return m_gradient_cache.back().second;
	}
};

class PartitionListViewItem : public TQListViewItem
{
public:
	PartitionListViewItem( const Partition *p,
	                      TQListView *parent,
	                      const TQString &c0,
	                      const TQString &c1,
	                      const TQString &c2,
	                      const TQString &c3,
	                      const TQString &c4,
	                      const TQString &c5,
	                      const TQString &c6,
	                      const TQString &c7 )
	: TQListViewItem( parent, c0, c1, c2, c3, c4, c5, c6, c7 ),
	  m_partition( p )
	{
	}

	const Partition *partition() const { return m_partition; }

protected:
	void paintCell( TQPainter *p, const TQColorGroup &cg, int column, int width, int align ) override
	{
		if (m_partition && m_partition->type != TYPE_UNALLOCATED && column == 0)
		{
			const TQFont old_f = p->font();
			TQFont f = old_f;
			f.setBold( true );
			p->setFont( f );
			TQListViewItem::paintCell( p, cg, column, width, align );
			p->setFont( old_f );
			return;
		}
		TQListViewItem::paintCell( p, cg, column, width, align );
	}

private:
	const Partition *m_partition;
};

class PartitionInfoUsageBar : public TQWidget
{
public:
	PartitionInfoUsageBar( const Partition &partition, TQWidget *parent )
	: TQWidget( parent ),
	  m_partition( partition )
	{
		setFixedSize( 400, 60 );
	}

protected:
	void paintEvent( TQPaintEvent * )
	{
		TQPainter p( this );
		p.fillRect( rect(), TQColor( TQString::fromUtf8( Utils::get_color( m_partition.get_filesystem_partition().fstype ).c_str() ) ) );

		if (m_partition.fstype != FS_UNALLOCATED)
		{
			int used = 0, unused = 0, unallocated = 0;
			if (m_partition.type == TYPE_EXTENDED)
			{
				used = 0;
				unused = 0;
				unallocated = 400 - BORDER * 2;
			}
			else if (m_partition.sector_usage_known())
			{
				m_partition.get_usage_triple( 400 - BORDER * 2, used, unused, unallocated );
			}
			else
			{
				used = 0;
				unused = 400 - BORDER * 2;
				unallocated = 0;
			}

			p.fillRect( BORDER, BORDER, used, 60 - 2 * BORDER, TQColor( "#F8F8BA" ) );
			p.fillRect( BORDER + used, BORDER, unused, 60 - 2 * BORDER, TQColor( "white" ) );
			p.fillRect( BORDER + used + unused, BORDER, unallocated, 60 - 2 * BORDER, TQColor( "darkgrey" ) );
		}

		p.setPen( TQColor( "black" ) );
		const TQString text = TQString::fromUtf8( m_partition.get_path().c_str() ) +
		                    "\n" +
		                    TQString::fromUtf8( Utils::format_size( m_partition.get_sector_length(), m_partition.sector_size ).c_str() );
		p.drawText( BORDER, BORDER, 400 - 2 * BORDER, 60 - 2 * BORDER, TQt::AlignCenter, text );
	}

private:
	enum { BORDER = 8 };
	const Partition &m_partition;
};

class Dialog_Partition_Copy_TQt : public TQDialog
{
public:
	class ResizerWidget : public TQWidget
	{
	public:
		ResizerWidget( Dialog_Partition_Copy_TQt *owner, TQWidget *parent )
		: TQWidget( parent ),
		  m_owner( owner ),
		  m_x_min_space_before( 0 ),
		  m_x_start( 0 ),
		  m_x_end( 500 ),
		  m_used( 0 ),
		  m_min_size( 0 ),
		  m_max_size( 500 ),
		  m_grip( 0 ),
		  m_drag_dx( 0 )
		{
			setMinimumSize( 500 + 20 + 16, 50 );
			setSizePolicy( TQSizePolicy::Fixed, TQSizePolicy::Fixed );
			setMouseTracking( true );
		}

		void set_x_min_space_before( int x ) { m_x_min_space_before = x; if (m_x_start < x) m_x_start = x; update(); }
		void set_x_start( int x ) { m_x_start = x; if (m_x_start < m_x_min_space_before) m_x_start = m_x_min_space_before; if (m_x_start > m_x_end) m_x_start = m_x_end; update(); }
		void set_x_end( int x ) { m_x_end = x; if (m_x_end < m_x_start) m_x_end = m_x_start; update(); }
		void set_used( int used ) { m_used = used; update(); }
		void set_size_limits( int min_sz, int max_sz ) { m_min_size = min_sz; m_max_size = max_sz; update(); }

		int get_x_start() const { return m_x_start; }
		int get_x_end() const { return m_x_end; }

	protected:
		void paintEvent( TQPaintEvent * ) override
		{
			TQPainter p( this );
			p.fillRect( rect(), colorGroup().background() );

			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int bar_y = 10;
			const int bar_w = 500;
			const int bar_h = 30;

			p.fillRect( bar_x, bar_y, bar_w, bar_h, TQColor( 0x66, 0x66, 0x66 ) );
			p.fillRect( bar_x, bar_y, bar_w, bar_h, TQColor( 0xff, 0xff, 0xff ) );
			p.setPen( TQColor( 0x55, 0x55, 0x55 ) );
			p.drawRect( bar_x, bar_y, bar_w, bar_h );

			const int px0 = bar_x + m_x_start;
			const int px1 = bar_x + m_x_end;
			if (px1 > px0)
			{
				p.fillRect( px0, bar_y + 1, px1 - px0, bar_h - 1, m_partition_color );
				if (m_used > 0)
				{
					int used_px = m_used;
					if (used_px > (m_x_end - m_x_start))
						used_px = (m_x_end - m_x_start);
					p.fillRect( px0, bar_y + 1, used_px, bar_h - 1, TQColor( 0xf8, 0xf8, 0xba ) );
				}
			}

			p.setPen( TQColor( 0x00, 0x00, 0x00 ) );
			p.drawRect( px0, bar_y, px1 - px0, bar_h );
			p.fillRect( px0 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );
			p.fillRect( px1 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );
		}

		void mousePressEvent( TQMouseEvent *ev ) override
		{
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int x = ev->x() - bar_x;
			const int left = m_x_start;
			const int right = m_x_end;
			m_grip = 0;
			if (abs( x - left ) <= 6)
				m_grip = 1;
			else if (abs( x - right ) <= 6)
				m_grip = 2;
			else if (x > left && x < right)
			{
				m_grip = 3;
				m_drag_dx = x - left;
			}
		}

		void mouseReleaseEvent( TQMouseEvent * ) override
		{
			m_grip = 0;
		}

		void mouseMoveEvent( TQMouseEvent *ev ) override
		{
			if (!m_grip)
				return;
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			int x = ev->x() - bar_x;
			if (x < 0)
				x = 0;
			if (x > 500)
				x = 500;

			if (m_grip == 1)
			{
				int new_start = x;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if ((m_x_end - new_start) < m_min_size)
					new_start = m_x_end - m_min_size;
				if ((m_x_end - new_start) > m_max_size)
					new_start = m_x_end - m_max_size;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				m_x_start = new_start;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 0 );
				update();
			}
			else if (m_grip == 2)
			{
				int new_end = x;
				if ((new_end - m_x_start) < m_min_size)
					new_end = m_x_start + m_min_size;
				if ((new_end - m_x_start) > m_max_size)
					new_end = m_x_start + m_max_size;
				if (new_end > 500)
					new_end = 500;
				m_x_end = new_end;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 1 );
				update();
			}
			else
			{
				int width = m_x_end - m_x_start;
				int new_start = x - m_drag_dx;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if (new_start + width > 500)
					new_start = 500 - width;
				m_x_start = new_start;
				m_x_end = new_start + width;
				if (m_owner)
					m_owner->on_resizer_move( m_x_start, m_x_end );
				update();
			}
		}

	public:
		void set_partition_color( const TQColor &c ) { m_partition_color = c; update(); }

	private:
		Dialog_Partition_Copy_TQt *m_owner;
		int m_x_min_space_before;
		int m_x_start;
		int m_x_end;
		int m_used;
		int m_min_size;
		int m_max_size;
		int m_grip;
		int m_drag_dx;
		TQColor m_partition_color;
	};

	Dialog_Partition_Copy_TQt( const Device &device,
	                          const FS &fs,
	                          const FS_Limits &fs_limits,
	                          const Partition &selected_partition,
	                          const Partition &copied_partition,
	                          TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_device( device ),
	  m_fs( fs ),
	  m_fs_limits( fs_limits ),
	  m_selected_partition( selected_partition ),
	  m_copied_partition( copied_partition )
	{
		setCaption( tr("Paste %1").arg( TQString::fromUtf8( copied_partition.get_path().c_str() ) ) );
		TQVBoxLayout *vb = new TQVBoxLayout( this );
		vb->setMargin( 8 );
		vb->setSpacing( 8 );

		TQFrame *frame = new TQFrame( this );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *fvb = new TQVBoxLayout( frame );
		fvb->setMargin( 6 );
		fvb->setSpacing( 6 );
		vb->addWidget( frame );

		TQGridLayout *grid = new TQGridLayout( fvb, 4, 2 );
		grid->setSpacing( 6 );
		grid->setColStretch( 0, 0 );
		grid->setColStretch( 1, 1 );

		grid->addWidget( new TQLabel( tr("Free space preceding (MiB):"), frame ), 0, 0 );
		m_spin_before = new TQSpinBox( frame );
		m_spin_before->setMinValue( 0 );
		m_spin_before->setMaxValue( 0 );
		m_spin_before->setLineStep( 1 );
		grid->addWidget( m_spin_before, 0, 1 );

		grid->addWidget( new TQLabel( tr("New size (MiB):"), frame ), 1, 0 );
		m_spin_size = new TQSpinBox( frame );
		m_spin_size->setMinValue( 0 );
		m_spin_size->setMaxValue( 0 );
		m_spin_size->setLineStep( 1 );
		grid->addWidget( m_spin_size, 1, 1 );

		grid->addWidget( new TQLabel( tr("Free space following (MiB):"), frame ), 2, 0 );
		m_spin_after = new TQSpinBox( frame );
		m_spin_after->setMinValue( 0 );
		m_spin_after->setMaxValue( 0 );
		m_spin_after->setLineStep( 1 );
		grid->addWidget( m_spin_after, 2, 1 );

		grid->addWidget( new TQLabel( tr("Align to:"), frame ), 3, 0 );
		m_combo_align = new TQComboBox( frame );
		m_combo_align->insertItem( tr("MiB") );
		m_combo_align->insertItem( tr("Cylinder") );
		m_combo_align->setCurrentItem( 0 );
		grid->addWidget( m_combo_align, 3, 1 );

		m_resizer = new ResizerWidget( this, frame );
		fvb->insertWidget( 0, m_resizer );

		m_lbl_minmax = new TQLabel( frame );
		m_lbl_minmax->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
		fvb->addWidget( m_lbl_minmax );

		TQHBoxLayout *bb = new TQHBoxLayout();
		bb->addStretch( 1 );
		TQPushButton *btn_ok = new TQPushButton( tr("Paste"), this );
		TQPushButton *btn_cancel = new TQPushButton( tr("Cancel"), this );
		connect( btn_ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( btn_cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		bb->addWidget( btn_ok );
		bb->addWidget( btn_cancel );
		vb->addLayout( bb );

		m_block_updates = 0;
		set_data();
		TQObject::connect( m_spin_before, TQT_SIGNAL(valueChanged(int)), this, TQT_SLOT(slot_before_changed(int)) );
		TQObject::connect( m_spin_size, TQT_SIGNAL(valueChanged(int)), this, TQT_SLOT(slot_size_changed(int)) );
		TQObject::connect( m_spin_after, TQT_SIGNAL(valueChanged(int)), this, TQT_SLOT(slot_after_changed(int)) );

		setMinimumSize( 520, 220 );
		resize( 520, 240 );
	}

	const Partition &get_new_partition()
	{
		prepare_new_partition();
		m_new_partition->status = STAT_COPY;
		GParted_Core::compose_partition_flags( *m_new_partition, m_device.disktype );
		return *m_new_partition;
	}

private slots:
	void slot_before_changed( int ) { on_spin_changed( 0 ); }
	void slot_size_changed( int ) { on_spin_changed( 1 ); }
	void slot_after_changed( int ) { on_spin_changed( 2 ); }

private:
	enum { SP_BEFORE = 0, SP_SIZE = 1, SP_AFTER = 2 };

	static int mb_needed_for_boot_record( const Partition &partition )
	{
		if (partition.inside_extended || partition.sector_start < MEBIBYTE / partition.sector_size)
			return 1;
		return 0;
	}

	static void snap_to_cylinder( const Device &device, Partition &partition )
	{
		if (device.cylsize <= 0)
			return;
		if (partition.type == TYPE_LOGICAL)
			return;

		Sector diff = 0;
		if (partition.sector_start > 0)
			diff = partition.sector_start % device.cylsize;
		if (diff > device.cylsize / 2)
			partition.sector_start += (device.cylsize - diff);
		else
			partition.sector_start -= diff;

		diff = (partition.sector_end + 1) % device.cylsize;
		if (diff > device.cylsize / 2)
			partition.sector_end += (device.cylsize - diff);
		else
			partition.sector_end -= diff;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	static void snap_to_mebibyte( const Device &, Partition &partition )
	{
		const Sector mib = MEBIBYTE / partition.sector_size;
		if (mib <= 0)
			return;
		Sector diff = 0;
		if (partition.sector_start >= 2 && partition.type != TYPE_LOGICAL)
		{
			diff = partition.sector_start % mib;
			partition.sector_start -= diff;
		}
		diff = (partition.sector_end + 1) % mib;
		partition.sector_end -= diff;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	static void snap_to_alignment( const Device &device, Partition &partition )
	{
		switch (partition.alignment)
		{
			case ALIGN_CYLINDER: snap_to_cylinder( device, partition ); break;
			case ALIGN_MEBIBYTE: snap_to_mebibyte( device, partition ); break;
			default: break;
		}
	}

	void set_minmax_text( int min_mib, int max_mib )
	{
		TQString s;
		s.sprintf( "Minimum size: %d MiB\t\tMaximum size: %d MiB", min_mib, max_mib );
		m_lbl_minmax->setText( s );
	}

	void set_data()
	{
		const int min_before_mib = mb_needed_for_boot_record( m_selected_partition );
		m_min_space_before_mib = min_before_mib;

		const double total_mib_d = Utils::sector_to_unit( m_selected_partition.get_sector_length(), m_selected_partition.sector_size, UNIT_MIB );
		m_total_mib = Utils::round( total_mib_d );

		const Sector copied_min_sectors = ( m_copied_partition.get_byte_length() + (m_selected_partition.sector_size - 1) ) / m_selected_partition.sector_size;
		const int copied_length_mib = (int)std::ceil( Utils::sector_to_unit( copied_min_sectors, m_selected_partition.sector_size, UNIT_MIB ) );

		FS_Limits lim = m_fs_limits;
		if ( m_fs.grow && ! GParted_Core::filesystem_resize_disallowed( m_copied_partition ) )
		{
			const Byte_Value max_dst_bytes = (Byte_Value)(m_total_mib - m_min_space_before_mib) * (Byte_Value)MEBIBYTE;
			if (!lim.max_size || lim.max_size > max_dst_bytes)
				lim.max_size = max_dst_bytes;
		}
		else
		{
			lim.max_size = m_copied_partition.get_byte_length();
		}

		const Sector min_resize = m_copied_partition.estimated_min_size();
		if (m_fs.fstype == FS_XFS)
			lim.min_size = std::max( lim.min_size, (Byte_Value)min_resize * (Byte_Value)m_copied_partition.sector_size );
		else
			lim.min_size = (Byte_Value)copied_length_mib * (Byte_Value)MEBIBYTE;

		m_work_limits = lim;
		const int min_size_mib = (int)std::ceil( lim.min_size / double(MEBIBYTE) );
		const int max_size_mib = (int)std::ceil( lim.max_size / double(MEBIBYTE) );

		m_mb_per_pixel = m_total_mib / 500.0;
		if (m_mb_per_pixel <= 0.0)
			m_mb_per_pixel = 1.0;

		m_block_updates = 1;
		m_spin_before->setMinValue( m_min_space_before_mib );
		m_spin_before->setMaxValue( m_total_mib - min_size_mib );
		m_spin_before->setValue( m_min_space_before_mib );

		m_spin_size->setMinValue( min_size_mib );
		m_spin_size->setMaxValue( max_size_mib );
		m_spin_size->setValue( copied_length_mib );

		m_spin_after->setMinValue( 0 );
		m_spin_after->setMaxValue( m_total_mib - m_min_space_before_mib - min_size_mib );
		m_spin_after->setValue( m_total_mib - m_min_space_before_mib - copied_length_mib );
		m_block_updates = 0;

		set_minmax_text( min_size_mib, max_size_mib );

		{
			TQColor part_col( 0xdd, 0xdd, 0xdd );
			const std::string col = Utils::get_color( m_copied_partition.fstype );
			if (!col.empty())
				part_col.setNamedColor( TQString::fromLatin1( col.c_str() ) );
			m_resizer->set_partition_color( part_col );
		}
		m_resizer->set_x_min_space_before( Utils::round( m_min_space_before_mib / m_mb_per_pixel ) );
		m_resizer->set_x_start( Utils::round( m_min_space_before_mib / m_mb_per_pixel ) );
		{
			int x_end = Utils::round( (m_min_space_before_mib + copied_length_mib) / (m_total_mib / 500.0) );
			m_resizer->set_x_end( x_end > 500 ? 500 : x_end );
		}
		{
			const Sector min_resize = m_copied_partition.estimated_min_size();
			m_resizer->set_used( Utils::round( Utils::sector_to_unit( min_resize, m_copied_partition.sector_size, UNIT_MIB ) / (m_total_mib / 500.0) ) );
		}
		m_resizer->set_size_limits(
			Utils::round( lim.min_size / (m_mb_per_pixel * (double)MEBIBYTE) ),
			Utils::round( lim.max_size / (m_mb_per_pixel * (double)MEBIBYTE) ) );

		m_new_partition.reset( m_copied_partition.clone() );
		m_new_partition->device_path = m_selected_partition.device_path;
		m_new_partition->inside_extended = m_selected_partition.inside_extended;
		m_new_partition->type = m_selected_partition.inside_extended ? TYPE_LOGICAL : TYPE_PRIMARY;
		m_new_partition->sector_size = m_selected_partition.sector_size;
		if ( m_copied_partition.sector_usage_known() )
		{
			const Byte_Value src_fs_bytes = ( m_copied_partition.sectors_used + m_copied_partition.sectors_unused ) * (Byte_Value)m_copied_partition.sector_size;
			const Byte_Value src_unused_bytes = m_copied_partition.sectors_unused * (Byte_Value)m_copied_partition.sector_size;
			const Sector dst_fs_sectors = (Sector)( (src_fs_bytes + m_selected_partition.sector_size - 1) / m_selected_partition.sector_size );
			const Sector dst_unused_sectors = (Sector)( (src_unused_bytes + m_selected_partition.sector_size - 1) / m_selected_partition.sector_size );
			m_new_partition->set_sector_usage( dst_fs_sectors, dst_unused_sectors );
		}
		else
		{
			m_new_partition->set_sector_usage( -1, -1 );
		}
	}

	void on_spin_changed( int which )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		const int before = m_spin_before->value();
		const int size = m_spin_size->value();
		const int after = m_spin_after->value();
		if (which == SP_BEFORE)
		{
			m_spin_after->setValue( m_total_mib - size - before );
			m_spin_size->setValue( m_total_mib - before - m_spin_after->value() );
		}
		else if (which == SP_SIZE)
		{
			m_spin_after->setValue( m_total_mib - before - size );
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - m_spin_after->value() );
		}
		else
		{
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - after );
			m_spin_size->setValue( m_total_mib - m_spin_before->value() - m_spin_after->value() );
		}
		if (!m_block_updates)
		{
			m_block_updates = 1;
			m_resizer->set_x_start( Utils::round( m_spin_before->value() / m_mb_per_pixel ) );
			m_resizer->set_x_end( 500 - Utils::round( m_spin_after->value() / m_mb_per_pixel ) );
			m_block_updates = 0;
		}
		m_block_updates = 0;
	}

	void on_resizer_move( int x_start, int x_end )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		m_spin_before->setValue( (int)Utils::round( x_start * m_mb_per_pixel ) );
		if (x_end == 500)
		{
			m_spin_after->setValue( 0 );
			m_spin_before->setValue( m_total_mib - m_spin_size->value() );
		}
		else
		{
			m_spin_after->setValue( m_total_mib - m_spin_before->value() - m_spin_size->value() );
		}
		m_block_updates = 0;
	}

	void on_resizer_resize( int x_start, int x_end, int arrow_type )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		m_spin_size->setValue( (int)Utils::round( (x_end - x_start) * m_mb_per_pixel ) );
		const int before_value = m_spin_before->value();
		if (arrow_type == 1)
		{
			if (x_end == 500)
			{
				m_spin_after->setValue( 0 );
				m_spin_size->setValue( m_total_mib - before_value );
			}
			else
			{
				m_spin_after->setValue( m_total_mib - before_value - m_spin_size->value() );
			}
		}
		else
		{
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - m_spin_after->value() );
		}
		m_block_updates = 0;
	}

	friend class ResizerWidget;

	void prepare_new_partition()
	{
		const int before_mib = m_spin_before->value();
		const int size_mib = m_spin_size->value();
		m_new_partition->alignment = (m_combo_align->currentItem() == 1) ? ALIGN_CYLINDER : ALIGN_MEBIBYTE;

		m_new_partition->sector_start = m_selected_partition.sector_start + (Sector)before_mib * (MEBIBYTE / m_new_partition->sector_size);
		m_new_partition->sector_end = m_new_partition->sector_start + (Sector)size_mib * (MEBIBYTE / m_new_partition->sector_size) - 1;
		if (m_new_partition->sector_end > m_selected_partition.sector_end)
			m_new_partition->sector_end = m_selected_partition.sector_end;
		m_new_partition->free_space_before = (Sector)before_mib * (MEBIBYTE / m_new_partition->sector_size);
		m_new_partition->strict_start = (before_mib == m_min_space_before_mib) ? true : false;
		snap_to_alignment( m_device, *m_new_partition );
	}

	const Device &m_device;
	const FS &m_fs;
	const FS_Limits m_fs_limits;
	FS_Limits m_work_limits;
	const Partition &m_selected_partition;
	const Partition &m_copied_partition;
	std::unique_ptr<Partition> m_new_partition;
	int m_total_mib;
	int m_min_space_before_mib;
	int m_block_updates;
	double m_mb_per_pixel;

	TQSpinBox *m_spin_before;
	TQSpinBox *m_spin_size;
	TQSpinBox *m_spin_after;
	TQComboBox *m_combo_align;
	TQLabel *m_lbl_minmax;
	ResizerWidget *m_resizer;
};

class Dialog_Partition_New_TQt : public TQDialog
{
public:
	class ResizerWidget : public TQWidget
	{
	public:
		ResizerWidget( Dialog_Partition_New_TQt *owner, TQWidget *parent )
		: TQWidget( parent ),
		  m_owner( owner ),
		  m_x_min_space_before( 0 ),
		  m_x_start( 0 ),
		  m_x_end( 500 ),
		  m_used( 0 ),
		  m_min_size( 0 ),
		  m_max_size( 500 ),
		  m_grip( 0 ),
		  m_drag_dx( 0 )
		{
			setMinimumSize( 500 + 20 + 16, 50 );
			setSizePolicy( TQSizePolicy::Fixed, TQSizePolicy::Fixed );
			setMouseTracking( true );
		}

		void set_x_min_space_before( int x ) { m_x_min_space_before = x; if (m_x_start < x) m_x_start = x; update(); }
		void set_x_start( int x ) { m_x_start = x; if (m_x_start < m_x_min_space_before) m_x_start = m_x_min_space_before; if (m_x_start > m_x_end) m_x_start = m_x_end; update(); }
		void set_x_end( int x ) { m_x_end = x; if (m_x_end < m_x_start) m_x_end = m_x_start; update(); }
		void set_used( int used ) { m_used = used; update(); }
		void set_size_limits( int min_sz, int max_sz ) { m_min_size = min_sz; m_max_size = max_sz; update(); }

	protected:
		void paintEvent( TQPaintEvent * ) override
		{
			TQPainter p( this );
			p.fillRect( rect(), colorGroup().background() );

			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int bar_y = 10;
			const int bar_w = 500;
			const int bar_h = 30;

			p.fillRect( bar_x, bar_y, bar_w, bar_h, TQColor( 0xff, 0xff, 0xff ) );
			p.setPen( TQColor( 0x55, 0x55, 0x55 ) );
			p.drawRect( bar_x, bar_y, bar_w, bar_h );

			const int px0 = bar_x + m_x_start;
			const int px1 = bar_x + m_x_end;
			if (px1 > px0)
			{
				p.fillRect( px0, bar_y + 1, px1 - px0, bar_h - 1, m_partition_color );
				if (m_used > 0)
				{
					int used_px = m_used;
					if (used_px > (m_x_end - m_x_start))
						used_px = (m_x_end - m_x_start);
					p.fillRect( px0, bar_y + 1, used_px, bar_h - 1, TQColor( 0xf8, 0xf8, 0xba ) );
				}
			}

			p.setPen( TQColor( 0x00, 0x00, 0x00 ) );
			p.drawRect( px0, bar_y, px1 - px0, bar_h );
			p.fillRect( px0 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );
			p.fillRect( px1 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );
		}

		void mousePressEvent( TQMouseEvent *ev ) override
		{
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int x = ev->x() - bar_x;
			const int left = m_x_start;
			const int right = m_x_end;
			m_grip = 0;
			if (abs( x - left ) <= 6)
				m_grip = 1;
			else if (abs( x - right ) <= 6)
				m_grip = 2;
			else if (x > left && x < right)
			{
				m_grip = 3;
				m_drag_dx = x - left;
			}
		}

		void mouseReleaseEvent( TQMouseEvent * ) override
		{
			m_grip = 0;
		}

		void mouseMoveEvent( TQMouseEvent *ev ) override
		{
			if (!m_grip)
				return;
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			int x = ev->x() - bar_x;
			if (x < 0)
				x = 0;
			if (x > 500)
				x = 500;

			if (m_grip == 1)
			{
				int new_start = x;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if ((m_x_end - new_start) < m_min_size)
					new_start = m_x_end - m_min_size;
				if ((m_x_end - new_start) > m_max_size)
					new_start = m_x_end - m_max_size;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				m_x_start = new_start;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 0 );
				update();
			}
			else if (m_grip == 2)
			{
				int new_end = x;
				if ((new_end - m_x_start) < m_min_size)
					new_end = m_x_start + m_min_size;
				if ((new_end - m_x_start) > m_max_size)
					new_end = m_x_start + m_max_size;
				if (new_end > 500)
					new_end = 500;
				m_x_end = new_end;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 1 );
				update();
			}
			else
			{
				int width = m_x_end - m_x_start;
				int new_start = x - m_drag_dx;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if (new_start + width > 500)
					new_start = 500 - width;
				m_x_start = new_start;
				m_x_end = new_start + width;
				if (m_owner)
					m_owner->on_resizer_move( m_x_start, m_x_end );
				update();
			}
		}

	public:
		void set_partition_color( const TQColor &c ) { m_partition_color = c; update(); }

	private:
		Dialog_Partition_New_TQt *m_owner;
		int m_x_min_space_before;
		int m_x_start;
		int m_x_end;
		int m_used;
		int m_min_size;
		int m_max_size;
		int m_grip;
		int m_drag_dx;
		TQColor m_partition_color;
	};

	Dialog_Partition_New_TQt( const Device &device,
	                         const Partition &selected_partition,
	                         bool any_extended,
	                         unsigned short new_count,
	                         const std::vector<FS> &filesystems,
	                         TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_device( device ),
	  m_selected_partition( selected_partition ),
	  m_any_extended( any_extended ),
	  m_new_count( new_count )
	{
		setCaption( tr("Create new Partition") );
		TQVBoxLayout *vb = new TQVBoxLayout( this );
		vb->setMargin( 8 );
		vb->setSpacing( 8 );

		TQFrame *frame = new TQFrame( this );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *fvb = new TQVBoxLayout( frame );
		fvb->setMargin( 6 );
		fvb->setSpacing( 6 );
		vb->addWidget( frame );

		m_resizer = new ResizerWidget( this, frame );
		fvb->addWidget( m_resizer );

		TQGridLayout *grid = new TQGridLayout( fvb, 8, 2 );
		grid->setSpacing( 6 );
		grid->setColStretch( 0, 0 );
		grid->setColStretch( 1, 1 );

		grid->addWidget( new TQLabel( tr("Create as:"), frame ), 0, 0 );
		m_combo_type = new TQComboBox( frame );
		m_combo_type->insertItem( tr("Primary Partition") );
		m_combo_type->insertItem( tr("Logical Partition") );
		m_combo_type->insertItem( tr("Extended Partition") );
		grid->addWidget( m_combo_type, 0, 1 );

		grid->addWidget( new TQLabel( tr("Partition name:"), frame ), 1, 0 );
		m_edit_name = new TQLineEdit( frame );
		grid->addWidget( m_edit_name, 1, 1 );

		grid->addWidget( new TQLabel( tr("File system:"), frame ), 2, 0 );
		m_combo_fs = new TQComboBox( frame );
		grid->addWidget( m_combo_fs, 2, 1 );

		grid->addWidget( new TQLabel( tr("Label:"), frame ), 3, 0 );
		m_edit_label = new TQLineEdit( frame );
		grid->addWidget( m_edit_label, 3, 1 );

		grid->addWidget( new TQLabel( tr("Free space preceding (MiB):"), frame ), 4, 0 );
		m_spin_before = new TQSpinBox( frame );
		m_spin_before->setLineStep( 1 );
		grid->addWidget( m_spin_before, 4, 1 );

		grid->addWidget( new TQLabel( tr("New size (MiB):"), frame ), 5, 0 );
		m_spin_size = new TQSpinBox( frame );
		m_spin_size->setLineStep( 1 );
		grid->addWidget( m_spin_size, 5, 1 );

		grid->addWidget( new TQLabel( tr("Free space following (MiB):"), frame ), 6, 0 );
		m_spin_after = new TQSpinBox( frame );
		m_spin_after->setLineStep( 1 );
		grid->addWidget( m_spin_after, 6, 1 );

		grid->addWidget( new TQLabel( tr("Align to:"), frame ), 7, 0 );
		m_combo_align = new TQComboBox( frame );
		m_combo_align->insertItem( tr("Cylinder") );
		m_combo_align->insertItem( tr("MiB") );
		m_combo_align->insertItem( tr("Strict") );
		m_combo_align->setCurrentItem( 1 );
		grid->addWidget( m_combo_align, 7, 1 );

		m_lbl_minmax = new TQLabel( frame );
		fvb->addWidget( m_lbl_minmax );

		TQHBoxLayout *bb = new TQHBoxLayout();
		bb->addStretch( 1 );
		TQPushButton *btn_ok = new TQPushButton( tr("Add"), this );
		TQPushButton *btn_cancel = new TQPushButton( tr("Cancel"), this );
		connect( btn_ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( btn_cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		bb->addWidget( btn_ok );
		bb->addWidget( btn_cancel );
		vb->addLayout( bb );

		build_filesystems_combo( filesystems );
		set_type_sensitivity();
		update_fs_limits_and_ui();

		m_last_type_idx = m_combo_type->currentItem();
		m_last_fs_idx = m_combo_fs->currentItem();
		m_last_before = m_spin_before->value();
		m_last_size = m_spin_size->value();
		m_last_after = m_spin_after->value();
		m_timer_id = startTimer( 100 );

		setMinimumSize( 560, 360 );
		resize( 560, 390 );
	}

	~Dialog_Partition_New_TQt() override
	{
		if (m_timer_id)
			killTimer( m_timer_id );
		m_timer_id = 0;
	}

	const Partition &get_new_partition()
	{
		prepare_new_partition();
		return *m_new_partition;
	}

private:
	enum { SP_BEFORE = 0, SP_SIZE = 1, SP_AFTER = 2 };

	void timerEvent( TQTimerEvent *ev ) override
	{
		if (!ev || ev->timerId() != m_timer_id)
			return;
		if (m_block_updates)
			return;

		const int type_idx = m_combo_type->currentItem();
		const int fs_idx = m_combo_fs->currentItem();
		if (type_idx != m_last_type_idx)
		{
			m_last_type_idx = type_idx;
			set_type_sensitivity();
			update_fs_limits_and_ui();
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
			return;
		}
		if (fs_idx != m_last_fs_idx)
		{
			m_last_fs_idx = fs_idx;
			update_fs_limits_and_ui();
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
			return;
		}

		const int before = m_spin_before->value();
		const int size = m_spin_size->value();
		const int after = m_spin_after->value();
		if (before != m_last_before)
		{
			on_spin_changed( SP_BEFORE );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
		else if (size != m_last_size)
		{
			on_spin_changed( SP_SIZE );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
		else if (after != m_last_after)
		{
			on_spin_changed( SP_AFTER );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
	}

	static int mb_needed_for_boot_record( const Partition &partition )
	{
		if (partition.inside_extended || partition.sector_start < MEBIBYTE / partition.sector_size)
			return 1;
		return 0;
	}

	static void snap_to_cylinder( const Device &device, Partition &partition )
	{
		if (device.cylsize <= 0)
			return;
		if (partition.type == TYPE_LOGICAL)
			return;
		Sector diff = 0;
		if (partition.sector_start > 0)
			diff = partition.sector_start % device.cylsize;
		if (diff > device.cylsize / 2)
			partition.sector_start += (device.cylsize - diff);
		else
			partition.sector_start -= diff;
		diff = (partition.sector_end + 1) % device.cylsize;
		if (diff > device.cylsize / 2)
			partition.sector_end += (device.cylsize - diff);
		else
			partition.sector_end -= diff;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	static void snap_to_mebibyte( const Device &, Partition &partition )
	{
		const Sector mib = MEBIBYTE / partition.sector_size;
		if (mib <= 0)
			return;
		Sector diff = 0;
		if (partition.sector_start >= 2 && partition.type != TYPE_LOGICAL)
		{
			diff = partition.sector_start % mib;
			partition.sector_start -= diff;
		}
		diff = (partition.sector_end + 1) % mib;
		partition.sector_end -= diff;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	static void snap_to_alignment( const Device &device, Partition &partition )
	{
		switch (partition.alignment)
		{
			case ALIGN_CYLINDER: snap_to_cylinder( device, partition ); break;
			case ALIGN_MEBIBYTE: snap_to_mebibyte( device, partition ); break;
			default: break;
		}
	}

	void set_type_sensitivity()
	{
		if (m_device.disktype != "msdos" && m_device.disktype != "dvh")
		{
			m_combo_type->setCurrentItem( 0 );
			return;
		}
		if (m_selected_partition.inside_extended)
		{
			m_combo_type->setCurrentItem( 1 );
			return;
		}
		if (m_any_extended)
			m_combo_type->setCurrentItem( 0 );
		else
			m_combo_type->setCurrentItem( 0 );
	}

	void build_filesystems_combo( const std::vector<FS> &filesystems )
	{
		m_filesystems.clear();
		for (unsigned int i = 0; i < filesystems.size(); i++)
		{
			if (GParted_Core::supported_filesystem( filesystems[i].fstype ) && filesystems[i].fstype != FS_LUKS)
				m_filesystems.push_back( filesystems[i] );
		}
		{
			FS fs_tmp;
			fs_tmp.fstype = FS_CLEARED;
			fs_tmp.create = FS::GPARTED;
			m_filesystems.push_back( fs_tmp );
			fs_tmp = FS();
			fs_tmp.fstype = FS_UNFORMATTED;
			fs_tmp.create = FS::GPARTED;
			m_filesystems.push_back( fs_tmp );
			fs_tmp = FS();
			fs_tmp.fstype = FS_EXTENDED;
			fs_tmp.create = FS::NONE;
			m_filesystems.push_back( fs_tmp );
		}

		m_combo_fs->clear();
		int default_fs = -1;
		for (unsigned int i = 0; i < m_filesystems.size(); i++)
		{
			if (m_filesystems[i].fstype == FS_EXTENDED)
				continue;
			m_combo_fs->insertItem( TQString::fromUtf8( Utils::get_filesystem_string( m_filesystems[i].fstype ).c_str() ) );
			if (default_fs < 0 && (m_filesystems[i].fstype == FS_EXT4 || m_filesystems[i].fstype == FS_EXT3 || m_filesystems[i].fstype == FS_EXT2) && m_filesystems[i].create)
				default_fs = (int)m_combo_fs->count() - 1;
		}
		if (default_fs < 0)
			default_fs = 0;
		m_combo_fs->setCurrentItem( default_fs );
	}

	FSType get_selected_fstype() const
	{
		const int idx = m_combo_fs->currentItem();
		int map = -1;
		for (unsigned int i = 0; i < m_filesystems.size(); i++)
		{
			if (m_filesystems[i].fstype == FS_EXTENDED)
				continue;
			map++;
			if (map == idx)
				return m_filesystems[i].fstype;
		}
		return FS_UNFORMATTED;
	}

	void update_fs_limits_and_ui()
	{
		m_new_partition.reset( m_selected_partition.clone() );
		const int min_before_mib = mb_needed_for_boot_record( m_selected_partition );
		m_min_space_before_mib = min_before_mib;
		m_start = m_selected_partition.sector_start;
		m_total_length = m_selected_partition.get_sector_length();
		m_total_mib = Utils::round( Utils::sector_to_unit( m_selected_partition.get_sector_length(), m_selected_partition.sector_size, UNIT_MIB ) );
		m_mb_per_pixel = m_total_mib / 500.0;
		if (m_mb_per_pixel <= 0.0)
			m_mb_per_pixel = 1.0;

		m_fs.fstype = get_selected_fstype();
		m_fs_limits = GParted_Core::get_filesystem_limits( m_fs.fstype, *m_new_partition );
		if (m_fs_limits.min_size < MEBIBYTE)
			m_fs_limits.min_size = MEBIBYTE;
		if (m_new_partition->get_byte_length() < m_fs_limits.min_size)
			m_fs_limits.min_size = m_new_partition->get_byte_length();
		if (!m_fs_limits.max_size || (m_fs_limits.max_size > (Byte_Value)(m_total_mib - m_min_space_before_mib) * (Byte_Value)MEBIBYTE))
			m_fs_limits.max_size = (Byte_Value)(m_total_mib - m_min_space_before_mib) * (Byte_Value)MEBIBYTE;

		const int min_size_mib = (int)std::ceil( m_fs_limits.min_size / double(MEBIBYTE) );
		const int max_size_mib = (int)std::ceil( m_fs_limits.max_size / double(MEBIBYTE) );
		TQString s;
		s.sprintf( "Minimum size: %d MiB\t\tMaximum size: %d MiB", min_size_mib, max_size_mib );
		m_lbl_minmax->setText( s );

		m_block_updates = 1;
		m_spin_before->setMinValue( m_min_space_before_mib );
		m_spin_before->setMaxValue( m_total_mib - min_size_mib );
		m_spin_after->setMinValue( 0 );
		m_spin_after->setMaxValue( m_total_mib - m_min_space_before_mib - min_size_mib );
		m_spin_size->setMinValue( min_size_mib );
		m_spin_size->setMaxValue( max_size_mib );
		m_spin_after->setValue( 0 );
		m_spin_size->setValue( max_size_mib );
		m_spin_before->setValue( m_min_space_before_mib );
		m_block_updates = 0;

		{
			TQColor part_col( 0xff, 0xff, 0xff );
			const std::string col = Utils::get_color( m_fs.fstype );
			if (!col.empty())
				part_col.setNamedColor( TQString::fromLatin1( col.c_str() ) );
			m_resizer->set_partition_color( part_col );
		}
		m_resizer->set_x_min_space_before( Utils::round( m_min_space_before_mib / m_mb_per_pixel ) );
		m_resizer->set_x_start( Utils::round( m_min_space_before_mib / m_mb_per_pixel ) );
		m_resizer->set_x_end( 500 );
		m_resizer->set_used( 0 );
		m_resizer->set_size_limits(
			Utils::round( m_fs_limits.min_size / (m_mb_per_pixel * (double)MEBIBYTE) ),
			Utils::round( m_fs_limits.max_size / (m_mb_per_pixel * (double)MEBIBYTE) ) );
	}

	void on_spin_changed( int which )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		const int before = m_spin_before->value();
		const int size = m_spin_size->value();
		const int after = m_spin_after->value();
		if (which == SP_BEFORE)
		{
			m_spin_after->setValue( m_total_mib - size - before );
			m_spin_size->setValue( m_total_mib - before - m_spin_after->value() );
		}
		else if (which == SP_SIZE)
		{
			m_spin_after->setValue( m_total_mib - before - size );
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - m_spin_after->value() );
		}
		else
		{
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - after );
			m_spin_size->setValue( m_total_mib - m_spin_before->value() - m_spin_after->value() );
		}
		m_resizer->set_x_start( Utils::round( m_spin_before->value() / m_mb_per_pixel ) );
		m_resizer->set_x_end( 500 - Utils::round( m_spin_after->value() / m_mb_per_pixel ) );
		m_block_updates = 0;
	}

	void on_resizer_move( int x_start, int x_end )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		m_spin_before->setValue( (int)Utils::round( x_start * m_mb_per_pixel ) );
		if (x_end == 500)
		{
			m_spin_after->setValue( 0 );
			m_spin_before->setValue( m_total_mib - m_spin_size->value() );
		}
		else
		{
			m_spin_after->setValue( m_total_mib - m_spin_before->value() - m_spin_size->value() );
		}
		m_block_updates = 0;
	}

	void on_resizer_resize( int x_start, int x_end, int arrow_type )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		m_spin_size->setValue( (int)Utils::round( (x_end - x_start) * m_mb_per_pixel ) );
		const int before_value = m_spin_before->value();
		if (arrow_type == 1)
		{
			if (x_end == 500)
			{
				m_spin_after->setValue( 0 );
				m_spin_size->setValue( m_total_mib - before_value );
			}
			else
			{
				m_spin_after->setValue( m_total_mib - before_value - m_spin_size->value() );
			}
		}
		else
		{
			m_spin_before->setValue( m_total_mib - m_spin_size->value() - m_spin_after->value() );
		}
		m_block_updates = 0;
	}

	friend class ResizerWidget;

	void prepare_new_partition()
	{
		PartitionType part_type = TYPE_PRIMARY;
		switch (m_combo_type->currentItem())
		{
			case 0: part_type = TYPE_PRIMARY; break;
			case 1: part_type = TYPE_LOGICAL; break;
			case 2: part_type = TYPE_EXTENDED; break;
			default: part_type = TYPE_PRIMARY; break;
		}

		Sector new_start = m_start + Sector(m_spin_before->value()) * (MEBIBYTE / m_new_partition->sector_size);
		Sector new_end = new_start + Sector(m_spin_size->value()) * (MEBIBYTE / m_new_partition->sector_size) - 1;
		if (new_start < m_new_partition->sector_start)
			new_start = m_new_partition->sector_start;
		if (new_end > m_new_partition->sector_end)
			new_end = m_new_partition->sector_end;
		if (new_start - m_new_partition->sector_start < MEBIBYTE / m_new_partition->sector_size)
			new_start = m_new_partition->sector_start;
		if (m_new_partition->sector_end - new_end < MEBIBYTE / m_new_partition->sector_size)
			new_end = m_new_partition->sector_end;

		Glib::ustring device_path = m_new_partition->device_path;
		Sector sector_size = m_new_partition->sector_size;
		bool inside_extended = m_new_partition->inside_extended;
		m_new_partition->Reset();
		m_new_partition->Set( device_path,
		                     Glib::ustring::compose( "New Partition #%1", m_new_count ),
		                     m_new_count,
		                     part_type,
		                     m_fs.fstype,
		                     new_start,
		                     new_end,
		                     sector_size,
		                     inside_extended,
		                     false );
		m_new_partition->status = STAT_NEW;
		m_new_partition->name = Utils::trim( Glib::ustring( m_edit_name->text().utf8() ) );
		m_new_partition->set_filesystem_label( Utils::trim( Glib::ustring( m_edit_label->text().utf8() ) ) );
		switch (m_combo_align->currentItem())
		{
			case 0: m_new_partition->alignment = ALIGN_CYLINDER; break;
			case 1: m_new_partition->alignment = ALIGN_MEBIBYTE; break;
			case 2: m_new_partition->alignment = ALIGN_STRICT; break;
			default: m_new_partition->alignment = ALIGN_MEBIBYTE; break;
		}
		GParted_Core::compose_partition_flags( *m_new_partition, m_device.disktype );
		m_new_partition->free_space_before = Sector(m_spin_before->value()) * (MEBIBYTE / m_new_partition->sector_size);
		snap_to_alignment( m_device, *m_new_partition );
	}

	const Device &m_device;
	const Partition &m_selected_partition;
	bool m_any_extended;
	unsigned short m_new_count;
	std::vector<FS> m_filesystems;
	FS m_fs;
	FS_Limits m_fs_limits;
	std::unique_ptr<Partition> m_new_partition;
	int m_block_updates = 0;

	int m_min_space_before_mib = 0;
	Sector m_start = 0;
	Sector m_total_length = 0;
	int m_total_mib = 0;
	double m_mb_per_pixel = 1.0;

	ResizerWidget *m_resizer;
	TQComboBox *m_combo_type;
	TQLineEdit *m_edit_name;
	TQComboBox *m_combo_fs;
	TQLineEdit *m_edit_label;
	TQSpinBox *m_spin_before;
	TQSpinBox *m_spin_size;
	TQSpinBox *m_spin_after;
	TQComboBox *m_combo_align;
	TQLabel *m_lbl_minmax;
	int m_timer_id = 0;
	int m_last_type_idx = -1;
	int m_last_fs_idx = -1;
	int m_last_before = -1;
	int m_last_size = -1;
	int m_last_after = -1;
};

class Dialog_Partition_Resize_Move_TQt : public TQDialog
{
public:
	class ResizerWidget : public TQWidget
	{
	public:
		ResizerWidget( Dialog_Partition_Resize_Move_TQt *owner, TQWidget *parent )
		: TQWidget( parent ),
		  m_owner( owner ),
		  m_x_min_space_before( 0 ),
		  m_x_start( 0 ),
		  m_x_end( 500 ),
		  m_used( 0 ),
		  m_min_size( 0 ),
		  m_max_size( 500 ),
		  m_grip( 0 ),
		  m_drag_dx( 0 ),
		  m_fixed_start( false ),
		  m_can_resize_left( true ),
		  m_can_resize_right( true )
		{
			setMinimumSize( 500 + 20 + 16, 50 );
			setSizePolicy( TQSizePolicy::Fixed, TQSizePolicy::Fixed );
			setMouseTracking( true );
		}

		void set_x_min_space_before( int x ) { m_x_min_space_before = x; if (m_x_start < x) m_x_start = x; update(); }
		void set_x_start( int x ) { m_x_start = x; if (m_x_start < m_x_min_space_before) m_x_start = m_x_min_space_before; if (m_x_start > m_x_end) m_x_start = m_x_end; update(); }
		void set_x_end( int x ) { m_x_end = x; if (m_x_end < m_x_start) m_x_end = m_x_start; update(); }
		void set_used( int used ) { m_used = used; update(); }
		void set_size_limits( int min_sz, int max_sz ) { m_min_size = min_sz; m_max_size = max_sz; update(); }
		void set_fixed_start( bool fixed ) { m_fixed_start = fixed; update(); }
		void set_can_resize_left( bool v ) { m_can_resize_left = v; update(); }
		void set_can_resize_right( bool v ) { m_can_resize_right = v; update(); }

		int get_x_start() const { return m_x_start; }
		int get_x_end() const { return m_x_end; }

	protected:
		void paintEvent( TQPaintEvent * ) override
		{
			TQPainter p( this );
			p.fillRect( rect(), colorGroup().background() );

			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int bar_y = 10;
			const int bar_w = 500;
			const int bar_h = 30;

			p.fillRect( bar_x, bar_y, bar_w, bar_h, TQColor( 0xff, 0xff, 0xff ) );
			p.setPen( TQColor( 0x55, 0x55, 0x55 ) );
			p.drawRect( bar_x, bar_y, bar_w, bar_h );

			const int px0 = bar_x + m_x_start;
			const int px1 = bar_x + m_x_end;
			if (px1 > px0)
			{
				p.fillRect( px0, bar_y + 1, px1 - px0, bar_h - 1, m_partition_color );
				if (m_used > 0)
				{
					int used_px = m_used;
					if (used_px > (m_x_end - m_x_start))
						used_px = (m_x_end - m_x_start);
					p.fillRect( px0, bar_y + 1, used_px, bar_h - 1, TQColor( 0xf8, 0xf8, 0xba ) );
				}
			}

			p.setPen( TQColor( 0x00, 0x00, 0x00 ) );
			p.drawRect( px0, bar_y, px1 - px0, bar_h );
			p.fillRect( px0 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );
			p.fillRect( px1 - 3, bar_y, 6, bar_h, TQColor( 0xcc, 0xcc, 0xcc ) );

			p.setPen( TQColor( 0x11, 0x11, 0x11 ) );
			p.setBrush( TQColor( 0x11, 0x11, 0x11 ) );
			const int mid_y = bar_y + (bar_h / 2);
			const int a = 4;
			if (m_can_resize_left && !m_fixed_start)
			{
				const int tip_x = px0 - 2;
				TQPointArray tri( 3 );
				tri[0] = TQPoint( tip_x,     mid_y );
				tri[1] = TQPoint( tip_x + a, mid_y - a );
				tri[2] = TQPoint( tip_x + a, mid_y + a );
				p.drawPolygon( tri );
			}
			if (m_can_resize_right)
			{
				const int tip_x = px1 + 2;
				TQPointArray tri( 3 );
				tri[0] = TQPoint( tip_x,     mid_y );
				tri[1] = TQPoint( tip_x - a, mid_y - a );
				tri[2] = TQPoint( tip_x - a, mid_y + a );
				p.drawPolygon( tri );
			}
		}

		void mousePressEvent( TQMouseEvent *ev ) override
		{
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			const int x = ev->x() - bar_x;
			const int left = m_x_start;
			const int right = m_x_end;
			m_grip = 0;
			if (!m_fixed_start && m_can_resize_left && abs( x - left ) <= 6)
				m_grip = 1;
			else if (m_can_resize_right && abs( x - right ) <= 6)
				m_grip = 2;
			else if (!m_fixed_start && x > left && x < right)
			{
				m_grip = 3;
				m_drag_dx = x - left;
			}
		}

		void mouseReleaseEvent( TQMouseEvent * ) override
		{
			m_grip = 0;
		}

		void mouseMoveEvent( TQMouseEvent *ev ) override
		{
			if (!m_grip)
				return;
			const int border = 8;
			const int gripper = 10;
			const int bar_x = border + gripper;
			int x = ev->x() - bar_x;
			if (x < 0)
				x = 0;
			if (x > 500)
				x = 500;

			if (m_grip == 1)
			{
				int new_start = x;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if ((m_x_end - new_start) < m_min_size)
					new_start = m_x_end - m_min_size;
				if ((m_x_end - new_start) > m_max_size)
					new_start = m_x_end - m_max_size;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				m_x_start = new_start;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 0 );
				update();
			}
			else if (m_grip == 2)
			{
				int new_end = x;
				if ((new_end - m_x_start) < m_min_size)
					new_end = m_x_start + m_min_size;
				if ((new_end - m_x_start) > m_max_size)
					new_end = m_x_start + m_max_size;
				if (new_end > 500)
					new_end = 500;
				m_x_end = new_end;
				if (m_owner)
					m_owner->on_resizer_resize( m_x_start, m_x_end, 1 );
				update();
			}
			else
			{
				int width = m_x_end - m_x_start;
				int new_start = x - m_drag_dx;
				if (new_start < m_x_min_space_before)
					new_start = m_x_min_space_before;
				if (new_start + width > 500)
					new_start = 500 - width;
				m_x_start = new_start;
				m_x_end = new_start + width;
				if (m_owner)
					m_owner->on_resizer_move( m_x_start, m_x_end );
				update();
			}
		}

	public:
		void set_partition_color( const TQColor &c ) { m_partition_color = c; update(); }

	private:
		Dialog_Partition_Resize_Move_TQt *m_owner;
		int m_x_min_space_before;
		int m_x_start;
		int m_x_end;
		int m_used;
		int m_min_size;
		int m_max_size;
		int m_grip;
		int m_drag_dx;
		bool m_fixed_start;
		bool m_can_resize_left;
		bool m_can_resize_right;
		TQColor m_partition_color;
	};

	Dialog_Partition_Resize_Move_TQt( const Device &device,
	                                 const FS &fs,
	                                 const FS_Limits &fs_limits,
	                                 const Partition &selected_partition,
	                                 const PartitionVector &display_partitions,
	                                 TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_device( device ),
	  m_fs( fs ),
	  m_fs_limits_in( fs_limits ),
	  m_display_partitions( display_partitions ),
	  m_selected_partition( selected_partition ),
	  m_fixed_start( false ),
	  m_total_mib( 0 ),
	  m_min_space_before_mib( 0 ),
	  m_mb_per_pixel( 1.0 ),
	  m_block_updates( 0 )
	{
		setCaption( tr("Resize/Move %1").arg( TQString::fromUtf8( selected_partition.get_path().c_str() ) ) );
		TQVBoxLayout *vb = new TQVBoxLayout( this );
		vb->setMargin( 8 );
		vb->setSpacing( 8 );

		TQFrame *frame = new TQFrame( this );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *fvb = new TQVBoxLayout( frame );
		fvb->setMargin( 6 );
		fvb->setSpacing( 6 );
		vb->addWidget( frame );

		m_resizer = new ResizerWidget( this, frame );
		fvb->addWidget( m_resizer );

		TQGridLayout *grid = new TQGridLayout( fvb, 4, 2 );
		grid->setSpacing( 6 );
		grid->setColStretch( 0, 0 );
		grid->setColStretch( 1, 1 );

		grid->addWidget( new TQLabel( tr("Free space preceding (MiB):"), frame ), 0, 0 );
		m_spin_before = new TQSpinBox( frame );
		m_spin_before->setMinValue( 0 );
		m_spin_before->setMaxValue( 0 );
		m_spin_before->setLineStep( 1 );
		grid->addWidget( m_spin_before, 0, 1 );

		grid->addWidget( new TQLabel( tr("New size (MiB):"), frame ), 1, 0 );
		m_spin_size = new TQSpinBox( frame );
		m_spin_size->setMinValue( 0 );
		m_spin_size->setMaxValue( 0 );
		m_spin_size->setLineStep( 1 );
		grid->addWidget( m_spin_size, 1, 1 );

		grid->addWidget( new TQLabel( tr("Free space following (MiB):"), frame ), 2, 0 );
		m_spin_after = new TQSpinBox( frame );
		m_spin_after->setMinValue( 0 );
		m_spin_after->setMaxValue( 0 );
		m_spin_after->setLineStep( 1 );
		grid->addWidget( m_spin_after, 2, 1 );

		grid->addWidget( new TQLabel( tr("Align to:"), frame ), 3, 0 );
		m_combo_align = new TQComboBox( frame );
		m_combo_align->insertItem( tr("MiB") );
		m_combo_align->insertItem( tr("Cylinder") );
		m_combo_align->insertItem( tr("Strict") );
		m_combo_align->setCurrentItem( 0 );
		grid->addWidget( m_combo_align, 3, 1 );

		m_lbl_minmax = new TQLabel( frame );
		m_lbl_minmax->setAlignment( TQt::AlignLeft | TQt::AlignVCenter );
		fvb->addWidget( m_lbl_minmax );

		TQHBoxLayout *bb = new TQHBoxLayout();
		bb->addStretch( 1 );
		TQPushButton *btn_ok = new TQPushButton( tr("OK"), this );
		TQPushButton *btn_cancel = new TQPushButton( tr("Cancel"), this );
		connect( btn_ok, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
		connect( btn_cancel, TQT_SIGNAL(clicked()), this, TQT_SLOT(reject()) );
		bb->addWidget( btn_ok );
		bb->addWidget( btn_cancel );
		vb->addLayout( bb );

		m_timer_id = startTimer( 100 );
		m_last_before = -1;
		m_last_size = -1;
		m_last_after = -1;

		init_from_selected();
		setMinimumSize( 560, 330 );
		resize( 560, 360 );
	}

	~Dialog_Partition_Resize_Move_TQt() override
	{
		if (m_timer_id)
			killTimer( m_timer_id );
		m_timer_id = 0;
	}

	const Partition &get_new_partition()
	{
		prepare_new_partition();
		return *m_new_partition;
	}

private:
	enum { SP_BEFORE = 0, SP_SIZE = 1, SP_AFTER = 2 };

	static int mb_needed_for_boot_record( const Partition &partition )
	{
		if (partition.inside_extended || partition.sector_start < MEBIBYTE / partition.sector_size)
			return 1;
		return 0;
	}

	static void snap_to_cylinder( const Device &device, Partition &partition )
	{
		if (device.cylsize <= 0)
			return;
		partition.sector_start = (partition.sector_start / device.cylsize) * device.cylsize;
		partition.sector_end = ((partition.sector_end + device.cylsize) / device.cylsize) * device.cylsize - 1;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	static void snap_to_mib( Partition &partition )
	{
		const Sector mib = (Sector)( MEBIBYTE / partition.sector_size );
		if (mib <= 0)
			return;
		partition.sector_start = (partition.sector_start / mib) * mib;
		partition.sector_end = ((partition.sector_end + mib) / mib) * mib - 1;
		if (partition.sector_end < partition.sector_start)
			partition.sector_end = partition.sector_start;
	}

	void snap_to_alignment( Partition &partition ) const
	{
		const int a = m_combo_align->currentItem();
		if (a == 1)
			snap_to_cylinder( m_device, partition );
		else if (a == 0)
			snap_to_mib( partition );
		else
			; // strict
	}

	void init_from_selected()
	{
		m_new_partition.reset( m_selected_partition.clone() );

		// Determine capabilities for moving start.
		m_fixed_start = true;
		if (m_fs.move && !m_selected_partition.busy && m_selected_partition.type != TYPE_UNPARTITIONED)
			m_fixed_start = false;

		m_spin_before->setEnabled( !m_fixed_start );
		m_resizer->set_fixed_start( m_fixed_start );

		// Find index in display vector.
		unsigned int idx = 0;
		for (; idx < m_display_partitions.size(); idx++)
			if (m_display_partitions[idx] == m_selected_partition)
				break;
		if (idx >= m_display_partitions.size())
			idx = 0;

		Sector previous = 0;
		Sector next = 0;
		const Partition *prev_unalloc = 0;
		if (idx >= 1 && m_display_partitions[idx - 1].type == TYPE_UNALLOCATED && !m_fixed_start)
		{
			previous = m_display_partitions[idx - 1].get_sector_length();
			m_start_sector = m_display_partitions[idx - 1].sector_start;
			prev_unalloc = &m_display_partitions[idx - 1];
		}
		else
			m_start_sector = m_selected_partition.sector_start;

		if (idx + 1 < m_display_partitions.size() && m_display_partitions[idx + 1].type == TYPE_UNALLOCATED)
			next = m_display_partitions[idx + 1].get_sector_length();

		m_min_space_before_mib = prev_unalloc ? mb_needed_for_boot_record( *prev_unalloc ) : 0;
		const Sector total_length = previous + m_selected_partition.get_sector_length() + next;
		m_total_mib = Utils::round( Utils::sector_to_unit( total_length, m_selected_partition.sector_size, UNIT_MIB ) );
		if (m_total_mib <= 0)
			m_total_mib = 1;
		m_mb_per_pixel = m_total_mib / 500.0;
		if (m_mb_per_pixel <= 0.0)
			m_mb_per_pixel = 1.0;

		FS_Limits lim = m_fs_limits_in;
		const bool can_shrink = ( (m_fs.shrink        && !m_selected_partition.busy) ||
		                         (m_fs.online_shrink &&  m_selected_partition.busy) );
		const bool can_grow = (m_fs.grow != FS::NONE);
		const bool can_move = (m_fs.move != FS::NONE);

		// MIN size
		if (can_shrink)
		{
			const Sector min_resize = m_selected_partition.estimated_min_size();
			const Byte_Value min_resize_bytes = (Byte_Value)min_resize * (Byte_Value)m_selected_partition.sector_size;
			if (lim.min_size < min_resize_bytes)
				lim.min_size = min_resize_bytes;
			if (!lim.min_size || lim.min_size < (Byte_Value)MEBIBYTE)
				lim.min_size = (Byte_Value)MEBIBYTE;
		}
		else
		{
			lim.min_size = m_selected_partition.get_byte_length();
		}

		// MAX size
		if (can_grow)
			lim.max_size = (Byte_Value)(m_total_mib - m_min_space_before_mib) * (Byte_Value)MEBIBYTE;
		else
			lim.max_size = m_selected_partition.get_byte_length();

		const int min_mib = (int)std::ceil( lim.min_size / double(MEBIBYTE) );
		const int max_mib = (int)std::ceil( lim.max_size / double(MEBIBYTE) );

		if (!m_fixed_start)
		{
			m_spin_before->setMinValue( m_min_space_before_mib );
			m_spin_before->setMaxValue( m_total_mib - (int)min_mib );
			m_spin_before->setValue( Utils::round( Utils::sector_to_unit( previous, m_selected_partition.sector_size, UNIT_MIB ) ) );
		}
		else
		{
			m_spin_before->setMinValue( 0 );
			m_spin_before->setMaxValue( 0 );
			m_spin_before->setValue( 0 );
		}

		m_spin_size->setMinValue( min_mib );
		m_spin_size->setMaxValue( max_mib );
		m_spin_size->setValue( Utils::round( Utils::sector_to_unit( m_selected_partition.get_sector_length(), m_selected_partition.sector_size, UNIT_MIB ) ) );

		const Sector after_min_sectors = (!can_grow && !can_move) ? next : 0;
		const int after_min_mib = Utils::round( Utils::sector_to_unit( after_min_sectors, m_selected_partition.sector_size, UNIT_MIB ) );
		m_spin_after->setMinValue( after_min_mib );
		m_spin_after->setMaxValue( m_total_mib - m_min_space_before_mib - min_mib );
		m_spin_after->setValue( Utils::round( Utils::sector_to_unit( next, m_selected_partition.sector_size, UNIT_MIB ) ) );

		m_resizer->set_x_min_space_before( Utils::round( m_min_space_before_mib / m_mb_per_pixel ) );
		m_resizer->set_x_start( Utils::round( Utils::sector_to_unit( previous, m_selected_partition.sector_size, UNIT_MIB ) / m_mb_per_pixel ) );
		{
			const int cur_mib = m_spin_size->value();
			const int x_end = Utils::round( (m_spin_before->value() + cur_mib) / m_mb_per_pixel );
			m_resizer->set_x_end( x_end > 500 ? 500 : x_end );
		}
		{
			const Sector min_resize = m_selected_partition.estimated_min_size();
			m_resizer->set_used( Utils::round( Utils::sector_to_unit( min_resize, m_selected_partition.sector_size, UNIT_MIB ) / (m_total_mib / 500.0) ) );
		}
		m_resizer->set_size_limits(
			Utils::round( lim.min_size / (m_mb_per_pixel * (double)MEBIBYTE) ),
			Utils::round( lim.max_size / (m_mb_per_pixel * (double)MEBIBYTE) ) );

		{
			TQColor part_col( 0xdd, 0xdd, 0xdd );
			const std::string col = Utils::get_color( m_selected_partition.fstype );
			if (!col.empty())
				part_col.setNamedColor( TQString::fromLatin1( col.c_str() ) );
			m_resizer->set_partition_color( part_col );
		}

		TQString mm = tr("Minimum size: %1 MiB, Maximum size: %2 MiB")
			.arg( TQString::number( min_mib ) )
			.arg( TQString::number( max_mib ) );
		m_lbl_minmax->setText( mm );

		// Update grip arrow availability (based on fixed start and whether size limits allow resizing).
		m_resizer->set_can_resize_left( !m_fixed_start );
		m_resizer->set_can_resize_right( min_mib != max_mib );

		m_last_before = m_spin_before->value();
		m_last_size = m_spin_size->value();
		m_last_after = m_spin_after->value();
	}

	void timerEvent( TQTimerEvent *ev ) override
	{
		if (!ev || ev->timerId() != m_timer_id)
			return;
		if (m_block_updates)
			return;

		const int before = m_spin_before->value();
		const int size = m_spin_size->value();
		const int after = m_spin_after->value();
		if (before != m_last_before)
		{
			on_spin_changed( SP_BEFORE );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
		else if (size != m_last_size)
		{
			on_spin_changed( SP_SIZE );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
		else if (after != m_last_after)
		{
			on_spin_changed( SP_AFTER );
			m_last_before = m_spin_before->value();
			m_last_size = m_spin_size->value();
			m_last_after = m_spin_after->value();
		}
	}

	void on_spin_changed( int which )
	{
		m_block_updates = 1;
		int before = m_spin_before->value();
		int size = m_spin_size->value();
		int after = m_spin_after->value();
		if (m_fixed_start)
			before = 0;

		int sum = before + size + after;
		if (sum != m_total_mib)
		{
			const int diff = m_total_mib - sum;
			if (which == SP_BEFORE)
			{
				after += diff;
				if (after < 0)
					after = 0;
				m_spin_after->setValue( after );
			}
			else if (which == SP_AFTER)
			{
				size += diff;
				if (size < m_spin_size->minValue())
					size = m_spin_size->minValue();
				if (size > m_spin_size->maxValue())
					size = m_spin_size->maxValue();
				m_spin_size->setValue( size );
			}
			else
			{
				after += diff;
				if (after < 0)
					after = 0;
				m_spin_after->setValue( after );
			}
		}

		const int x_start = Utils::round( (m_fixed_start ? 0.0 : (double)m_spin_before->value()) / m_mb_per_pixel );
		m_resizer->set_x_start( x_start );
		m_resizer->set_x_end( Utils::round( ( (m_fixed_start ? 0.0 : (double)m_spin_before->value()) + (double)m_spin_size->value() ) / m_mb_per_pixel ) );
		m_block_updates = 0;
	}

	void on_resizer_move( int x_start, int x_end )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		const int before = Utils::round( x_start * m_mb_per_pixel );
		const int size = Utils::round( (x_end - x_start) * m_mb_per_pixel );
		int after = m_total_mib - before - size;
		if (after < 0)
			after = 0;
		m_spin_before->setValue( before );
		m_spin_size->setValue( size );
		m_spin_after->setValue( after );
		m_block_updates = 0;
	}

	void on_resizer_resize( int x_start, int x_end, int arrow_type )
	{
		if (m_block_updates)
			return;
		m_block_updates = 1;
		const int before = Utils::round( x_start * m_mb_per_pixel );
		const int size = Utils::round( (x_end - x_start) * m_mb_per_pixel );
		int after = m_total_mib - before - size;
		if (after < 0)
			after = 0;
		if (arrow_type == 0)
			m_spin_before->setValue( before );
		m_spin_size->setValue( size );
		m_spin_after->setValue( after );
		m_block_updates = 0;
	}

	friend class ResizerWidget;

	void prepare_new_partition()
	{
		std::unique_ptr<Partition> tmp( m_selected_partition.clone() );
		Partition &p = *tmp;
		const int before_mib = m_fixed_start ? 0 : m_spin_before->value();
		const int size_mib = m_spin_size->value();
		p.sector_start = m_start_sector + (Sector)( ( (Byte_Value)before_mib * (Byte_Value)MEBIBYTE ) / (Byte_Value)p.sector_size );
		const Sector len_sectors = (Sector)( ( (Byte_Value)size_mib * (Byte_Value)MEBIBYTE + (Byte_Value)p.sector_size - 1 ) / (Byte_Value)p.sector_size );
		p.sector_end = p.sector_start + len_sectors - 1;
		snap_to_alignment( p );
		p.alignment = (m_combo_align->currentItem() == 2) ? ALIGN_STRICT : (m_combo_align->currentItem() == 1 ? ALIGN_CYLINDER : ALIGN_MEBIBYTE);
		m_new_partition = std::move( tmp );
	}

	const Device &m_device;
	const FS m_fs;
	const FS_Limits m_fs_limits_in;
	const PartitionVector &m_display_partitions;
	const Partition &m_selected_partition;
	std::unique_ptr<Partition> m_new_partition;
	ResizerWidget *m_resizer;
	TQSpinBox *m_spin_before;
	TQSpinBox *m_spin_size;
	TQSpinBox *m_spin_after;
	TQComboBox *m_combo_align;
	TQLabel *m_lbl_minmax;
	bool m_fixed_start;
	int m_total_mib;
	int m_min_space_before_mib;
	Sector m_start_sector;
	double m_mb_per_pixel;
	int m_block_updates;
	int m_timer_id = 0;
	int m_last_before = -1;
	int m_last_size = -1;
	int m_last_after = -1;
};

class Dialog_Partition_Info_TQt : public TQDialog
{
public:
	Dialog_Partition_Info_TQt( const Partition &partition, TQWidget *parent )
	: TQDialog( parent, 0, true ),
	  m_partition( partition )
	{
		setCaption( tr("Information about %1").arg( TQString::fromUtf8( partition.get_path().c_str() ) ) );

	TQVBoxLayout *vb = new TQVBoxLayout( this );
	vb->setMargin( 8 );
	vb->setSpacing( 8 );
	{
		TQFrame *frame = new TQFrame( this );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQHBoxLayout *hb = new TQHBoxLayout( frame );
		hb->setMargin( 10 );
		hb->setSpacing( 0 );
		hb->addStretch( 1 );
		hb->addWidget( new PartitionInfoUsageBar( m_partition, frame ) );
		hb->addStretch( 1 );
		vb->addWidget( frame );
	}

	TQWidget *container = new TQWidget( this );
	{
		TQVBoxLayout *cvb = new TQVBoxLayout( container );
		cvb->setMargin( 0 );
		cvb->setSpacing( 8 );
		build_device_type_frame( container, cvb );
		build_info_grid( container, cvb );
		build_messages( container, cvb );
		cvb->addStretch( 1 );
	}
	vb->addWidget( container, 1 );

	TQHBoxLayout *bb = new TQHBoxLayout();
	bb->addStretch( 1 );
	TQPushButton *btn_close = new TQPushButton( tr("Close"), this );
	connect( btn_close, TQT_SIGNAL(clicked()), this, TQT_SLOT(accept()) );
	bb->addWidget( btn_close );
	bb->setSpacing( 6 );
	vb->addLayout( bb );

	setMinimumSize( 640, 420 );
	resize( 640, (partition.have_messages() || partition.fstype == FS_LVM2_PV || partition.fstype == FS_LUKS) ? 520 : 440 );
	}

private:
	static void add_field( TQGridLayout *grid, int row, int col, const TQString &field, const TQString &value,
	                       int align_label, int align_value )
	{
		TQLabel *l = new TQLabel( field, grid->mainWidget() );
		TQFont f = l->font();
		f.setBold( true );
		l->setFont( f );
		l->setAlignment( align_label | TQt::AlignVCenter );
		grid->addWidget( l, row, col );
		TQLabel *v = new TQLabel( value, grid->mainWidget() );
		v->setTextFormat( TQt::PlainText );
		v->setAlignment( align_value | TQt::AlignVCenter );
		grid->addWidget( v, row, col + 1 );
	}

	static void add_field_left( TQGridLayout *grid, int row, const TQString &field, const TQString &value )
	{
		add_field( grid, row, 0, field, value, TQt::AlignLeft, TQt::AlignLeft );
	}

	static void add_field_right( TQGridLayout *grid, int row, const TQString &field, const TQString &value )
	{
		add_field( grid, row, 2, field, value, TQt::AlignRight, TQt::AlignRight );
	}

	static TQString join_ustrings( const std::vector<Glib::ustring> &v, const char *sep )
	{
		TQString out;
		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (i)
				out += sep;
			out += TQString::fromUtf8( v[i].c_str() );
		}
		return out;
	}

	void build_device_type_frame( TQWidget *container, TQVBoxLayout *cvb )
	{
		TQFrame *frame = new TQFrame( container );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *vb = new TQVBoxLayout( frame );
		vb->setMargin( 6 );
		vb->setSpacing( 6 );
		{
			TQLabel *hdr = new TQLabel( tr("Device"), frame );
			TQFont f = hdr->font();
			f.setBold( true );
			hdr->setFont( f );
			vb->addWidget( hdr );
		}

		TQGridLayout *grid = new TQGridLayout( vb, 0, 4 );
		grid->setSpacing( 6 );
		grid->setColStretch( 1, 1 );
		grid->setColStretch( 3, 1 );
		grid->setColSpacing( 1, 16 );

		TQString dtype = tr("Unknown");
		switch (detect_device_type_tqt( m_partition.device_path ))
		{
			case DEVTYPE_USB_STORAGE: dtype = tr("USB storage"); break;
			case DEVTYPE_NVME_SSD:    dtype = tr("NVMe SSD"); break;
			case DEVTYPE_SATA_SSD:    dtype = tr("SATA SSD"); break;
			case DEVTYPE_MECHANICAL:  dtype = tr("Mechanical disk"); break;
			case DEVTYPE_UNKNOWN:
			default: break;
		}

		add_field_left( grid, 0, tr("Device type:"), dtype );
		cvb->addWidget( frame );
	}

	void build_info_grid( TQWidget *container, TQVBoxLayout *cvb )
	{
		const Partition &fsptn = m_partition.get_filesystem_partition();
		TQFrame *frame = new TQFrame( container );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *vb = new TQVBoxLayout( frame );
		vb->setMargin( 6 );
		vb->setSpacing( 6 );

		{
			TQLabel *hdr = new TQLabel( tr("File System"), frame );
			TQFont f = hdr->font();
			f.setBold( true );
			hdr->setFont( f );
			vb->addWidget( hdr );
		}

		TQGridLayout *grid = new TQGridLayout( vb, 0, 4 );
		grid->setSpacing( 6 );
		grid->setColStretch( 1, 1 );
		grid->setColStretch( 3, 1 );
		grid->setColSpacing( 1, 16 );

		int r = 0;
		add_field_left( grid, r, tr("File system:"), TQString::fromUtf8( fsptn.get_filesystem_string().c_str() ) );
		if (fsptn.fstype != FS_UNALLOCATED && fsptn.type != TYPE_EXTENDED)
			add_field_left( grid, r + 1, tr("Label:"), TQString::fromUtf8( fsptn.get_filesystem_label().c_str() ) );
		if (fsptn.fstype != FS_UNALLOCATED && fsptn.type != TYPE_EXTENDED)
			add_field_left( grid, r + 2, tr("UUID:"), TQString::fromUtf8( fsptn.uuid.c_str() ) );
		if (fsptn.fstype != FS_UNALLOCATED && fsptn.type != TYPE_EXTENDED)
		{
			const Glib::ustring &mp = fsptn.get_mountpoint();
			if (!mp.empty())
				add_field_left( grid, r + 3, tr("Mounted on:"), TQString::fromUtf8( mp.c_str() ) );
			else
				add_field_left( grid, r + 3, tr("Mounted on:"), tr("Not mounted") );
		}

		if (m_partition.sector_usage_known())
		{
			const Sector sused = m_partition.get_sectors_used();
			const Sector sunused = m_partition.get_sectors_unused();
			const Sector stotal = sused + sunused;
			int pused = 0;
			int punused = 0;
			if (stotal > 0)
			{
				pused = (int)( (100.0 * (double)sused / (double)stotal) + 0.5 );
				punused = 100 - pused;
			}
			TQString used_str = TQString::fromUtf8( Utils::format_size( sused, m_partition.sector_size ).c_str() );
			TQString unused_str = TQString::fromUtf8( Utils::format_size( sunused, m_partition.sector_size ).c_str() );
			used_str += TQString::fromLatin1(" (") + TQString::number( pused ) + TQString::fromLatin1("%)");
			unused_str += TQString::fromLatin1(" (") + TQString::number( punused ) + TQString::fromLatin1("%)");
			add_field_right( grid, r, tr("Used:"), used_str );
			add_field_right( grid, r + 1, tr("Unused:"), unused_str );
			add_field_right( grid, r + 2, tr("Size:"), TQString::fromUtf8( Utils::format_size( m_partition.get_sector_length(), m_partition.sector_size ).c_str() ) );
		}
		else
		{
			add_field_right( grid, r, tr("Size:"), TQString::fromUtf8( Utils::format_size( m_partition.get_sector_length(), m_partition.sector_size ).c_str() ) );
		}

		cvb->addWidget( frame );

		TQFrame *frame2 = new TQFrame( container );
		frame2->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *vb2 = new TQVBoxLayout( frame2 );
		vb2->setMargin( 6 );
		vb2->setSpacing( 6 );
		{
			TQLabel *hdr = new TQLabel( tr("Partition"), frame2 );
			TQFont f = hdr->font();
			f.setBold( true );
			hdr->setFont( f );
			vb2->addWidget( hdr );
		}
		TQGridLayout *grid2 = new TQGridLayout( vb2, 0, 4 );
		grid2->setSpacing( 6 );
		grid2->setColStretch( 1, 1 );
		grid2->setColStretch( 3, 1 );
		grid2->setColSpacing( 1, 16 );
		int r2 = 0;
		add_field_left( grid2, r2, tr("Path:"), TQString::fromUtf8( m_partition.get_path().c_str() ) );
		if (m_partition.fstype != FS_UNALLOCATED && m_partition.status != STAT_NEW)
		{
			add_field_left( grid2, r2 + 1, tr("Name:"), TQString::fromUtf8( m_partition.name.c_str() ) );
			add_field_left( grid2, r2 + 2, tr("Flags:"), join_ustrings( m_partition.get_flags(), ", " ) );
		}

		{
			TQString ss;
			ss.sprintf( "%lld", (long long)m_partition.sector_start );
			add_field_right( grid2, r2, tr("First sector:"), ss );
			ss.sprintf( "%lld", (long long)m_partition.sector_end );
			add_field_right( grid2, r2 + 1, tr("Last sector:"), ss );
			ss.sprintf( "%lld", (long long)m_partition.get_sector_length() );
			add_field_right( grid2, r2 + 2, tr("Total sectors:"), ss );
		}
		cvb->addWidget( frame2 );
	}

	void build_messages( TQWidget *container, TQVBoxLayout *cvb )
	{
		if (!m_partition.have_messages())
			return;
		TQFrame *frame = new TQFrame( container );
		frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
		TQVBoxLayout *vb = new TQVBoxLayout( frame );
		vb->setMargin( 6 );
		vb->setSpacing( 6 );
		{
			TQLabel *hdr = new TQLabel( tr("Warning:"), frame );
			TQFont f = hdr->font();
			f.setBold( true );
			hdr->setFont( f );
			vb->addWidget( hdr );
		}
		TQString msg;
		{
			std::vector<Glib::ustring> messages = m_partition.get_messages();
			for (unsigned int i = 0; i < messages.size(); i++)
			{
				if (msg.length())
					msg += "\n\n";
				msg += TQString::fromUtf8( Utils::trim_trailing_new_line( messages[i] ).c_str() );
			}
		}
		TQLabel *lbl = new TQLabel( msg, frame );
		lbl->setTextFormat( TQt::PlainText );
		lbl->setAlignment( TQt::AlignLeft | TQt::AlignTop | TQt::WordBreak );
		lbl->setSizePolicy( TQSizePolicy::Expanding, TQSizePolicy::Minimum );
		vb->addWidget( lbl );
		cvb->addWidget( frame );
	}

	const Partition &m_partition;
};

Win_GParted_TQt::Win_GParted_TQt( const std::vector<Glib::ustring> & user_devices )
{
	m_core.set_user_devices( user_devices );
	m_current_device = -1;
	m_copied_partition = 0;
	m_new_count = 1;
	m_selected_partition = 0;
	m_selected_partition_path.clear();
	m_selected_partition_sector_start = 0;
	m_selected_partition_sector_end = 0;
	m_selected_partition_type = 0;
	m_in_selection_sync = 0;
	m_menu_edit = 0;
	m_menu_view = 0;
	m_menu_device = 0;
	m_menu_partition = 0;
	m_menu_gparted = 0;
	m_menu_gparted_devices = 0;
	m_menu_partition_format_to = 0;
	m_menu_partition_mount_on = 0;
	m_menu_partition_format_id = -1;
	m_menu_view_device_info_id = -1;
	m_menu_view_pending_ops_id = -1;
	m_menu_device_refresh_devices_id = -1;
	m_menu_device_create_table_id = -1;
	m_menu_device_create_image_id = -1;
	m_menu_device_restore_image_id = -1;
	m_menu_device_secure_erase_id = -1;
	m_menu_device_load_image_id = -1;
	m_menu_device_detach_virtual_id = -1;
	m_menu_device_smart_infos_id = -1;
	m_menu_device_simple_benchmark_id = -1;
	m_menu_gparted_devices_id = -1;
	m_menu_partition_new_id = -1;
	m_menu_partition_delete_id = -1;
	m_menu_partition_resize_id = -1;
	m_menu_partition_copy_id = -1;
	m_menu_partition_paste_id = -1;
	m_menu_partition_create_image_id = -1;
	m_menu_partition_restore_image_id = -1;
	m_menu_partition_secure_erase_id = -1;
	m_menu_partition_toggle_crypt_id = -1;
	m_menu_partition_toggle_fs_id = -1;
	m_menu_partition_mount_on_id = -1;
	m_menu_partition_name_id = -1;
	m_menu_partition_flags_id = -1;
	m_menu_partition_check_id = -1;
	m_menu_partition_label_id = -1;
	m_menu_partition_uuid_id = -1;
	m_menu_edit_undo_id = -1;
	m_menu_edit_clear_id = -1;
	m_menu_edit_apply_id = -1;
	m_menu_partition_format_to_ids.clear();
	m_menu_partition_format_to_fstypes.clear();
	m_menu_partition_mount_on_ids.clear();
	m_menu_partition_mount_on_mountpoints.clear();
	m_menu_gparted_devices_ids.clear();
	m_btn_refresh = 0;
	m_btn_new = 0;
	m_btn_delete = 0;
	m_btn_resize_move = 0;
	m_btn_copy = 0;
	m_btn_paste = 0;
	m_btn_export_commands = 0;
	m_ops_popup = 0;
	m_ops_popup_undo_id = -1;
	m_ops_popup_clear_id = -1;
	m_ops_popup_apply_id = -1;
	m_ops_popup_close_id = -1;
	m_virtual_attaches.clear();
	setUsesTextLabel( true );

	setCaption( APP_BRAND_NAME );
	if (!tdeparted_app_icon_pixmap().isNull())
		setIcon( tdeparted_app_icon_pixmap() );
	setMinimumSize( 1080, 580 );
	resize( 1080, 580 );
	init_menubar();
	init_toolbar();
	init_layout();
	init_statusbar();

	TQTimer::singleShot( 0, this, TQT_SLOT(start_initial_scan()) );
}

void Win_GParted_TQt::start_initial_scan()
{
	if (m_visualdisk_scanning_label)
		m_visualdisk_scanning_label->show();
	if (m_visualdisk_widget)
		m_visualdisk_widget->hide();
	if (m_details_list)
		m_details_list->clear();
	if (statusBar())
		statusBar()->message( tr("Scanning devices & partitions...") );
	if (tqApp)
		tqApp->processEvents();

	refresh_devices();

	if (m_visualdisk_scanning_label)
		m_visualdisk_scanning_label->hide();
	if (m_visualdisk_widget)
		m_visualdisk_widget->show();
	if (statusBar())
		statusBar()->message( TQString() );
}

void Win_GParted_TQt::menu_device_create_partition_table()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;

	if (m_operations.size() > 0)
	{
		TQString msg = tr("A new partition table cannot be created when there are pending operations.");
		TQString sec = tr("Use the Edit menu to either clear or apply all operations before creating a new partition table.");
		TQMessageBox::information( this, tr("Create Partition Table"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	const int active_count = active_partitions_on_device_count_tqt( m_devices[m_current_device] );
	if (active_count > 0)
	{
		TQString msg = tr("%1 partition(s) are currently active on device %2")
			.arg( TQString::number( active_count ) )
			.arg( TQString::fromUtf8( m_devices[m_current_device].get_path().c_str() ) );
		TQString sec = tr("A new partition table cannot be created when there are active partitions.");
		sec += "  ";
		sec += tr("Active partitions are those that are in use, such as a mounted file system, or enabled swap space.");
		sec += "\n";
		sec += tr("Use Partition menu options, such as unmount or swapoff, to deactivate all partitions on this device before creating a new partition table.");
		TQMessageBox::information( this, tr("Create Partition Table"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	Dialog_Disklabel_TQt dlg( m_devices[m_current_device], this );
	if (dlg.exec() != TQDialog::Accepted)
		return;

	const Glib::ustring disklabel = dlg.get_disklabel();
	if (disklabel.empty())
		return;

	if (!m_core.set_disklabel( m_devices[m_current_device], disklabel ))
	{
		TQMessageBox::critical( this, tr("Create Partition Table"), tr("Error while creating partition table"), TQMessageBox::Ok, TQMessageBox::NoButton );
	}

	menu_device_refresh_devices();
}

void Win_GParted_TQt::menu_device_create_disk_image()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Create Disk Image"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (!ensure_device_unused_tqt( this, m_devices[m_current_device], tr("Create Disk Image") ))
		return;
	const Device &dev = m_devices[m_current_device];
	const uint64_t bytes_total = (uint64_t)dev.length * (uint64_t)dev.sector_size;
	ImagingCreateOpts_TQt o;
	TQString summary = tr("Source: %1\nSize: %2 MiB")
		.arg( TQString::fromUtf8( dev.get_path().c_str() ) )
		.arg( TQString::number( (unsigned long)(bytes_total >> 20) ) );
	if (!run_imaging_create_options_dialog_tqt( this, tr("Create Disk Image"), summary, TQString::fromLatin1("disk.img"), o ))
		return;
	ImagingWorker_TQt *w = new ImagingWorker_TQt( dev.get_path(), Glib::ustring( o.out_path.local8Bit().data() ), bytes_total, 1, 0, 0, o.rescue_zerofill, o.used_space_only ? 1 : 0, o.sha256, o.sha256_verify );
	Dialog_Imaging_Progress_TQt dlg( tr("Create Disk Image"), tr("Creating image of %1").arg( TQString::fromUtf8( dev.get_path().c_str() ) ), this );
	(void)dlg.run_modal_imaging( w );
}

void Win_GParted_TQt::menu_device_restore_disk_image()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Restore Disk Image"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (!ensure_device_unused_tqt( this, m_devices[m_current_device], tr("Restore Disk Image") ))
		return;
	TQString filename = TQFileDialog::getOpenFileName( TQString(), TQString::fromLatin1("Images (*.img *.bin *.xz);;All Files (*)"), this, "open_disk_image", tr("Restore Disk Image") );
	if (filename.isEmpty())
		return;
	const Glib::ustring src_path( filename.local8Bit().data() );
	const uint64_t src_size = imaging_file_size_u64( src_path );
	if (src_size == 0)
	{
		TQMessageBox::critical( this, tr("Restore Disk Image"), tr("Failed to read image file size"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	TQString dev = TQString::fromUtf8( m_devices[m_current_device].get_path().c_str() );
	if (!destructive_type_confirm_tqt( this,
	                                 tr("Restore Disk Image"),
	                                 dev,
	                                 tr("All existing data will be lost") ))
		return;

	const Device &d = m_devices[m_current_device];
	const uint64_t bytes_total = (uint64_t)d.length * (uint64_t)d.sector_size;
	if (src_size > bytes_total)
	{
		TQMessageBox::critical( this, tr("Restore Disk Image"), tr("Image file is larger than the target device"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	ImagingRestoreOpts_TQt o;
	TQString summary = tr("Source: %1\nSize: %2 MiB\nTarget: %3")
		.arg( filename )
		.arg( TQString::number( (unsigned long)(src_size >> 20) ) )
		.arg( TQString::fromUtf8( d.get_path().c_str() ) );
	if (!run_imaging_restore_options_dialog_tqt( this, tr("Restore Disk Image"), summary, o ))
		return;

	ImagingWorker_TQt *w = new ImagingWorker_TQt( src_path, d.get_path(), src_size, 0, 1, 1, 0, 0, o.sha256, o.sha256_verify );
	Dialog_Imaging_Progress_TQt dlg( tr("Restore Disk Image"), tr("Restoring image to %1").arg( TQString::fromUtf8( d.get_path().c_str() ) ), this );
	const bool ok = dlg.run_modal_imaging( w );
	if (ok)
	{
		refresh_devices();
		m_selected_partition = 0;
		m_selected_partition_path.clear();
		m_selected_partition_sector_start = 0;
		m_selected_partition_sector_end = 0;
		m_selected_partition_type = 0;
		if (m_details_list)
			m_details_list->clearSelection();
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
		refresh_visual();
		update_window_title();
		update_valid_actions();
	}
}

static bool secure_erase_confirm_strict_tqt( TQWidget *parent, const TQString &title, const TQString &device_path, const TQString &backend_label )
{
	TQString msg = Win_GParted_TQt::tr("You are about to permanently erase all data on device %1").arg( device_path );
	TQString sec = Win_GParted_TQt::tr("This action cannot be undone.");
	sec += TQString::fromLatin1("\n\n");
	sec += Win_GParted_TQt::tr("Method: %1").arg( backend_label );
	const int r1 = TQMessageBox::warning( parent, title, msg + TQString::fromLatin1("\n\n") + sec, Win_GParted_TQt::tr("Continue"), Win_GParted_TQt::tr("Cancel") );
	if (r1 != 0)
		return false;

	TQString label = Win_GParted_TQt::tr("Type the device path to confirm:\n%1").arg( device_path );
	while (1)
	{
		Dialog_Type_Confirm_TQt dlg( title, label, device_path, parent );
		if (dlg.exec() != TQDialog::Accepted)
			return false;
		if (dlg.matches())
			return true;
		dlg.show_mismatch_error();
	}
}

static bool device_is_nvme_path_tqt( const Glib::ustring &dev )
{
	if (dev.size() < 10)
		return false;
	return (dev.find("/dev/nvme") == 0);
}

static bool secure_erase_run_nvme_sanitize_tqt( const Glib::ustring &dev, Glib::ustring &error_msg )
{
	Glib::ustring output;
	Glib::ustring error;
	const Glib::ustring cmd = "nvme sanitize " + Glib::shell_quote( dev ) + " -a 2";
	const bool ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
		error_msg = "# " + cmd + "\n" + error;
	return ok;
}

static bool secure_erase_run_blkdiscard_tqt( const Glib::ustring &dev, Glib::ustring &error_msg )
{
	Glib::ustring output;
	Glib::ustring error;
	const Glib::ustring cmd = "blkdiscard -v " + Glib::shell_quote( dev );
	const bool ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
	{
		error_msg = "# " + cmd + "\n" + output + error;
		if (error.find("BLKDISCARD") != Glib::ustring::npos ||
		    error.find("Operation not supported") != Glib::ustring::npos ||
		    error.find("Op\303\251ration non support\303\251e") != Glib::ustring::npos)
		{
			error_msg += "\n\n";
			error_msg += "This device does not support discard/TRIM.\n";
			error_msg += "Suggested manual wipe (slow):\n";
			error_msg += "# wipefs -a " + dev + "\n";
			error_msg += "# dd if=/dev/zero of=" + dev + " bs=16M status=progress oflag=direct\n";
		}
		return false;
	}
	return true;
}

static bool hdparm_get_identity_tqt( const Glib::ustring &dev, Glib::ustring &output, Glib::ustring &error )
{
	const Glib::ustring cmd = "hdparm -I " + Glib::shell_quote( dev );
	return !Utils::execute_command( cmd, output, error );
}

static bool secure_erase_run_ata_hdparm_tqt( const Glib::ustring &dev, Glib::ustring &error_msg )
{
	Glib::ustring id_out;
	Glib::ustring id_err;
	if (!hdparm_get_identity_tqt( dev, id_out, id_err ))
	{
		error_msg = "# hdparm -I " + dev + "\n" + id_err;
		return false;
	}
	if (id_out.find(" not frozen") != Glib::ustring::npos)
	{
		;
	}
	else if (id_out.find(" frozen") != Glib::ustring::npos)
	{
		error_msg = "hdparm reports device is frozen.\n\n" + id_out;
		return false;
	}
	if (id_out.find("Security:") == Glib::ustring::npos)
	{
		error_msg = "hdparm did not report ATA Security feature set.\n\n" + id_out;
		return false;
	}

	char pwbuf[48];
	{
		const unsigned long long t = (unsigned long long)time( 0 );
		const unsigned long long p = (unsigned long long)getpid();
		snprintf( pwbuf, sizeof(pwbuf), "tdeparted-%llx-%llx", t, p );
		pwbuf[sizeof(pwbuf) - 1] = 0;
	}
	const Glib::ustring pw( pwbuf );

	Glib::ustring output;
	Glib::ustring error;
	Glib::ustring cmd;
	bool ok;

	cmd = "hdparm --user-master u --security-set-pass " + Glib::shell_quote( pw ) + " " + Glib::shell_quote( dev );
	ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
	{
		error_msg = "# " + cmd + "\n" + error;
		return false;
	}
	if (output.find("not supported") != Glib::ustring::npos || output.find("disabled") != Glib::ustring::npos ||
	    error.find("not supported") != Glib::ustring::npos  || error.find("disabled") != Glib::ustring::npos)
	{
		error_msg = "# " + cmd + "\n" + output + error;
		return false;
	}

	output.clear();
	error.clear();
	cmd = "hdparm --user-master u --security-erase " + Glib::shell_quote( pw ) + " " + Glib::shell_quote( dev );
	ok = !Utils::execute_command( cmd, output, error );
	if (!ok)
		error_msg = "# " + cmd + "\n" + error;
	if (ok)
	{
		if (output.find("not supported") != Glib::ustring::npos || output.find("disabled") != Glib::ustring::npos ||
		    error.find("not supported") != Glib::ustring::npos  || error.find("disabled") != Glib::ustring::npos)
		{
			error_msg = "# " + cmd + "\n" + output + error;
			return false;
		}
	}
	return ok;
}

static bool secure_erase_device_tqt( TQWidget *parent, const Device &dev )
{
	const Glib::ustring dev_path = dev.get_path();
	if (dev_path.empty())
		return false;
	const TQString tdev = TQString::fromUtf8( dev_path.c_str() );

	const DeviceType_TQt dtype = detect_device_type_tqt( dev_path );
	const bool is_nvme = (dtype == DEVTYPE_NVME_SSD) || device_is_nvme_path_tqt( dev_path );
	const bool is_usb = (!is_nvme && dtype == DEVTYPE_USB_STORAGE);
	TQString backend;
	if (is_nvme)
		backend = Win_GParted_TQt::tr("NVMe sanitize (block erase)");
	else if (is_usb)
		backend = Win_GParted_TQt::tr("Discard (blkdiscard)");
	else
		backend = Win_GParted_TQt::tr("ATA secure erase (hdparm)");

	if (!secure_erase_confirm_strict_tqt( parent, Win_GParted_TQt::tr("Secure Erase"), tdev, backend ))
		return false;

	Glib::ustring error_msg;
	bool ok;
	if (is_nvme)
		ok = secure_erase_run_nvme_sanitize_tqt( dev_path, error_msg );
	else if (is_usb)
		ok = secure_erase_run_blkdiscard_tqt( dev_path, error_msg );
	else
		ok = secure_erase_run_ata_hdparm_tqt( dev_path, error_msg );

	if (!ok)
	{
		TQMessageBox::critical( parent, Win_GParted_TQt::tr("Secure Erase"), Win_GParted_TQt::tr("Secure erase failed") + TQString::fromLatin1("\n\n") + TQString::fromUtf8( error_msg.c_str() ), TQMessageBox::Ok, TQMessageBox::NoButton );
		return false;
	}

	TQMessageBox::information( parent, Win_GParted_TQt::tr("Secure Erase"), Win_GParted_TQt::tr("Secure erase command completed."), TQMessageBox::Ok, TQMessageBox::NoButton );
	return true;
}

void Win_GParted_TQt::menu_device_secure_erase()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Secure Erase"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (!ensure_device_unused_tqt( this, m_devices[m_current_device], tr("Secure Erase") ))
		return;
	if (!secure_erase_device_tqt( this, m_devices[m_current_device] ))
		return;
	menu_device_refresh_devices();
}

void Win_GParted_TQt::action_partition_secure_erase()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Secure Erase"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (!ensure_device_unused_tqt( this, m_devices[m_current_device], tr("Secure Erase") ))
		return;
	if (!secure_erase_device_tqt( this, m_devices[m_current_device] ))
		return;
	menu_device_refresh_devices();
}

void Win_GParted_TQt::action_partition_create_image()
{
	if (!m_selected_partition)
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Create Partition Image"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	if (!ensure_partition_unused_tqt( this, m_selected_partition->get_filesystem_partition(), tr("Create Partition Image") ))
		return;
	const Partition &fsptn = m_selected_partition->get_filesystem_partition();
	const uint64_t bytes_total = (uint64_t)fsptn.get_byte_length();
	ImagingCreateOpts_TQt o;
	TQString summary = tr("Source: %1\nSize: %2 MiB")
		.arg( TQString::fromUtf8( fsptn.get_path().c_str() ) )
		.arg( TQString::number( (unsigned long)(bytes_total >> 20) ) );
	if (!run_imaging_create_options_dialog_tqt( this, tr("Create Partition Image"), summary, TQString::fromLatin1("partition.img"), o ))
		return;
	ImagingWorker_TQt *w = new ImagingWorker_TQt( fsptn.get_path(), Glib::ustring( o.out_path.local8Bit().data() ), bytes_total, 1, 0, 0, o.rescue_zerofill, o.used_space_only ? 1 : 0, o.sha256, o.sha256_verify );
	Dialog_Imaging_Progress_TQt dlg( tr("Create Partition Image"), tr("Creating image of %1").arg( TQString::fromUtf8( fsptn.get_path().c_str() ) ), this );
	(void)dlg.run_modal_imaging( w );
}

void Win_GParted_TQt::action_partition_restore_image()
{
	if (!m_selected_partition)
		return;
	if (m_operations.size() > 0)
	{
		TQMessageBox::information( this, tr("Restore Partition Image"), tr("This action cannot be performed when there are pending operations."), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	const Partition &fsptn = m_selected_partition->get_filesystem_partition();
	if (!ensure_partition_unused_tqt( this, fsptn, tr("Restore Partition Image") ))
		return;
	TQString filename = TQFileDialog::getOpenFileName( TQString(), TQString::fromLatin1("Images (*.img *.bin *.xz);;All Files (*)"), this, "open_partition_image", tr("Restore Partition Image") );
	if (filename.isEmpty())
		return;
	const Glib::ustring src_path( filename.local8Bit().data() );
	const uint64_t src_size = imaging_file_size_u64( src_path );
	if (src_size == 0)
	{
		TQMessageBox::critical( this, tr("Restore Partition Image"), tr("Failed to read image file size"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	TQString dev = TQString::fromUtf8( fsptn.get_path().c_str() );
	if (!destructive_type_confirm_tqt( this,
	                                 tr("Restore Partition Image"),
	                                 dev,
	                                 tr("All existing data will be lost") ))
		return;

	const uint64_t bytes_total = (uint64_t)fsptn.get_byte_length();
	if (src_size > bytes_total)
	{
		TQMessageBox::critical( this, tr("Restore Partition Image"), tr("Image file is larger than the target partition"), TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}
	ImagingRestoreOpts_TQt o;
	TQString summary = tr("Source: %1\nSize: %2 MiB\nTarget: %3")
		.arg( filename )
		.arg( TQString::number( (unsigned long)(src_size >> 20) ) )
		.arg( TQString::fromUtf8( fsptn.get_path().c_str() ) );
	if (!run_imaging_restore_options_dialog_tqt( this, tr("Restore Partition Image"), summary, o ))
		return;

	ImagingWorker_TQt *w = new ImagingWorker_TQt( src_path, fsptn.get_path(), src_size, 0, 1, 1, 0, 0, o.sha256, o.sha256_verify );
	Dialog_Imaging_Progress_TQt dlg( tr("Restore Partition Image"), tr("Restoring image to %1").arg( TQString::fromUtf8( fsptn.get_path().c_str() ) ), this );
	const bool ok = dlg.run_modal_imaging( w );
	if (ok)
	{
		refresh_devices();
		m_selected_partition = 0;
		m_selected_partition_path.clear();
		m_selected_partition_sector_start = 0;
		m_selected_partition_sector_end = 0;
		m_selected_partition_type = 0;
		if (m_details_list)
			m_details_list->clearSelection();
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
		refresh_visual();
		update_window_title();
		update_valid_actions();
	}
}

Win_GParted_TQt::~Win_GParted_TQt()
{
	delete m_copied_partition;
	m_copied_partition = 0;
}

void Win_GParted_TQt::refresh_device_information()
{
	if (!m_lbl_dev_path)
		return;

	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
	{
		m_lbl_dev_model->setText( TQString::null );
		m_lbl_dev_serial->setText( TQString::null );
		if (m_lbl_dev_type) m_lbl_dev_type->setText( TQString::null );
		m_lbl_dev_size->setText( TQString::null );
		m_lbl_dev_path->setText( TQString::null );
		m_lbl_dev_disktype->setText( TQString::null );
		if (m_lbl_dev_heads) m_lbl_dev_heads->setText( TQString::null );
		if (m_lbl_dev_sectors) m_lbl_dev_sectors->setText( TQString::null );
		if (m_lbl_dev_cylinders) m_lbl_dev_cylinders->setText( TQString::null );
		if (m_lbl_dev_total_sectors) m_lbl_dev_total_sectors->setText( TQString::null );
		m_lbl_dev_sector_size->setText( TQString::null );
		return;
	}

	const Device &d = m_devices[m_current_device];
	const Glib::ustring size_str = Utils::format_size( d.length, d.sector_size );

	m_lbl_dev_model->setText( TQString::fromUtf8( d.model.c_str() ) );
	m_lbl_dev_serial->setText( TQString::fromUtf8( d.serial_number.c_str() ) );
	if (m_lbl_dev_type)
	{
		TQString dtype = tr("Unknown");
		switch (detect_device_type_tqt( d.get_path() ))
		{
			case DEVTYPE_USB_STORAGE: dtype = tr("USB storage"); break;
			case DEVTYPE_NVME_SSD:    dtype = tr("NVMe SSD"); break;
			case DEVTYPE_SATA_SSD:    dtype = tr("SATA SSD"); break;
			case DEVTYPE_MECHANICAL:  dtype = tr("Mechanical disk"); break;
			case DEVTYPE_UNKNOWN:
			default: break;
		}
		m_lbl_dev_type->setText( dtype );
	}
	m_lbl_dev_size->setText( TQString::fromUtf8( size_str.c_str() ) );
	m_lbl_dev_path->setText( TQString::fromUtf8( d.get_path().c_str() ) );
	m_lbl_dev_disktype->setText( TQString::fromUtf8( d.disktype.c_str() ) );
	if (m_lbl_dev_heads) m_lbl_dev_heads->setText( TQString::number( d.heads ) );
	if (m_lbl_dev_sectors) m_lbl_dev_sectors->setText( TQString::number( d.sectors ) );
	if (m_lbl_dev_cylinders) m_lbl_dev_cylinders->setText( TQString::number( d.cylinders ) );
	if (m_lbl_dev_total_sectors) m_lbl_dev_total_sectors->setText( TQString::number( (long long)d.length ) );

	{
		char buf[64];
		snprintf( buf, sizeof(buf), "%d", d.sector_size );
		m_lbl_dev_sector_size->setText( TQString::fromLatin1( buf ) );
	}

	update_window_title();
}

void Win_GParted_TQt::update_window_title()
{
	TQString title;
	if (m_current_device >= 0 && m_current_device < (int)m_devices.size())
		title = TQString::fromUtf8( m_devices[m_current_device].get_path().c_str() ) + TQString::fromLatin1(" - ") + TQString::fromLatin1( APP_BRAND_NAME );
	else
		title = TQString::fromLatin1( APP_BRAND_NAME );
	setCaption( title );
}

void Win_GParted_TQt::init_menubar()
{
	m_menu_gparted = new TQPopupMenu( this );
	{
		int id;
		{
			const TQPixmap pm = load_icon_by_name( "view-refresh" );
			if (!pm.isNull())
				id = m_menu_gparted->insertItem( pm, tr("Refresh Devices"), this, TQT_SLOT(menu_device_refresh_devices()), TQKeySequence("Ctrl+R") );
			else
				id = m_menu_gparted->insertItem( tr("Refresh Devices"), this, TQT_SLOT(menu_device_refresh_devices()), TQKeySequence("Ctrl+R") );
		}
		m_menu_device_refresh_devices_id = id;
		m_menu_gparted_devices = new TQPopupMenu( this );
		TQObject::connect( m_menu_gparted_devices, TQT_SIGNAL(activated(int)), this, TQT_SLOT(menu_gparted_devices_select(int)) );
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "device" );
			if (!pm.isNull())
				id = m_menu_gparted->insertItem( pm, tr("Devices"), m_menu_gparted_devices );
			else
				id = m_menu_gparted->insertItem( tr("Devices"), m_menu_gparted_devices );
		}
		m_menu_gparted_devices_id = id;
		m_menu_gparted->setItemEnabled( id, false );
		m_menu_gparted->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "quit" );
			if (!pm.isNull())
				id = m_menu_gparted->insertItem( pm, tr("Quit"), this, TQT_SLOT(menu_quit()), TQKeySequence("Ctrl+Q") );
			else
				id = m_menu_gparted->insertItem( tr("Quit"), this, TQT_SLOT(menu_quit()), TQKeySequence("Ctrl+Q") );
		}
	}
	menuBar()->insertItem( tr("tdeParted"), m_menu_gparted );

	m_menu_edit = new TQPopupMenu( this );
	{
		int id;
		{
			const TQPixmap pm = load_icon_by_name( "edit-undo" );
			if (!pm.isNull())
				id = m_menu_edit->insertItem( pm, tr("Undo Last Operation"), this, TQT_SLOT(action_undo()), TQKeySequence("Ctrl+Z") );
			else
				id = m_menu_edit->insertItem( tr("Undo Last Operation"), this, TQT_SLOT(action_undo()), TQKeySequence("Ctrl+Z") );
		}
		m_menu_edit_undo_id = id;
		m_menu_edit->setItemEnabled( id, false );
		id = m_menu_edit->insertItem( tr("Clear All Operations"), this, TQT_SLOT(action_clear_operations()) );
		m_menu_edit_clear_id = id;
		m_menu_edit->setItemEnabled( id, false );
		{
			const TQPixmap pm = load_icon_by_name( "gtk-execute" );
			if (!pm.isNull())
				id = m_menu_edit->insertItem( pm, tr("Apply All Operations"), this, TQT_SLOT(action_apply()), TQKeySequence("Ctrl+Return") );
			else
				id = m_menu_edit->insertItem( tr("Apply All Operations"), this, TQT_SLOT(action_apply()), TQKeySequence("Ctrl+Return") );
		}
		m_menu_edit_apply_id = id;
		m_menu_edit->setItemEnabled( id, false );
	}
	menuBar()->insertItem( tr("Edit"), m_menu_edit );

	m_menu_view = new TQPopupMenu( this );
	m_menu_view->setCheckable( true );
	{
		const TQPixmap pm_info = load_embedded_ui_icon_by_name_tqt( "info" );
		if (!pm_info.isNull())
			m_menu_view_device_info_id = m_menu_view->insertItem( pm_info, tr("Device Information"), this, TQT_SLOT(menu_view_device_information()) );
		else
			m_menu_view_device_info_id = m_menu_view->insertItem( tr("Device Information"), this, TQT_SLOT(menu_view_device_information()) );
		const TQPixmap pm_pending = load_embedded_ui_icon_by_name_tqt( "pending" );
		if (!pm_pending.isNull())
			m_menu_view_pending_ops_id = m_menu_view->insertItem( pm_pending, tr("Pending Operations"), this, TQT_SLOT(menu_view_pending_operations()) );
		else
			m_menu_view_pending_ops_id = m_menu_view->insertItem( tr("Pending Operations"), this, TQT_SLOT(menu_view_pending_operations()) );
	}
	m_menu_view->setItemChecked( m_menu_view_device_info_id, false );
	m_menu_view->setItemChecked( m_menu_view_pending_ops_id, false );
	m_menu_view->insertSeparator();
	{
		int id;
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "file_system" );
			if (!pm.isNull())
				id = m_menu_view->insertItem( pm, tr("File System Support"), this, TQT_SLOT(menu_view_filesystem_support()) );
			else
				id = m_menu_view->insertItem( tr("File System Support"), this, TQT_SLOT(menu_view_filesystem_support()) );
		}
		m_menu_view->setItemEnabled( id, true );
	}
	menuBar()->insertItem( tr("View"), m_menu_view );

	m_menu_device = new TQPopupMenu( this );
	{
		int id;
		id = m_menu_device->insertItem( tr("Create Partition Table") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_create_partition_table()) );
		m_menu_device_create_table_id = id;
		m_menu_device->setItemEnabled( id, false );
		m_menu_device->insertSeparator();
		{
			TQPopupMenu *submenu_image = new TQPopupMenu( this );
			id = submenu_image->insertItem( tr("Create Disk Image") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_create_disk_image()) );
			m_menu_device_create_image_id = id;
			submenu_image->setItemEnabled( id, false );
			id = submenu_image->insertItem( tr("Restore Disk Image") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_restore_disk_image()) );
			m_menu_device_restore_image_id = id;
			submenu_image->setItemEnabled( id, false );
			submenu_image->insertSeparator();
			id = submenu_image->insertItem( tr("Load Disk Image") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_load_disk_image()) );
			m_menu_device_load_image_id = id;
			submenu_image->setItemEnabled( id, true );
			id = submenu_image->insertItem( tr("Detach Virtual Device"), this, TQT_SLOT(menu_device_detach_virtual_device()) );
			m_menu_device_detach_virtual_id = id;
			submenu_image->setItemEnabled( id, false );
			m_menu_device->insertItem( tr("Image"), submenu_image );
		}
		m_menu_device->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "sec_erase" );
			if (!pm.isNull())
				id = m_menu_device->insertItem( pm, tr("Secure Erase") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_secure_erase()) );
			else
				id = m_menu_device->insertItem( tr("Secure Erase") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_secure_erase()) );
		}
		m_menu_device_secure_erase_id = id;
		m_menu_device->setItemEnabled( id, false );
		m_menu_device->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "smart" );
			if (!pm.isNull())
				id = m_menu_device->insertItem( pm, tr("SMART infos") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_smart_infos()) );
			else
				id = m_menu_device->insertItem( tr("SMART infos") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_smart_infos()) );
		}
		m_menu_device_smart_infos_id = id;
		m_menu_device->setItemEnabled( id, false );
		m_menu_device->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "bench" );
			if (!pm.isNull())
				id = m_menu_device->insertItem( pm, tr("Quick Benchmark") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_simple_benchmark()) );
			else
				id = m_menu_device->insertItem( tr("Quick Benchmark") + TQString::fromLatin1("..."), this, TQT_SLOT(menu_device_simple_benchmark()) );
		}
		m_menu_device_simple_benchmark_id = id;
		m_menu_device->setItemEnabled( id, false );
		m_menu_device->insertSeparator();
	}
	menuBar()->insertItem( tr("Device"), m_menu_device );

	m_menu_partition = new TQPopupMenu( this );
	{
		int id;
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "new" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("New"), this, TQT_SLOT(action_new()) );
			else
				id = m_menu_partition->insertItem( tr("New"), this, TQT_SLOT(action_new()) );
		}
		m_menu_partition_new_id = id;
		m_menu_partition->setItemEnabled( id, false );
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "delete" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Delete"), this, TQT_SLOT(action_delete()) );
			else
				id = m_menu_partition->insertItem( tr("Delete"), this, TQT_SLOT(action_delete()) );
		}
		m_menu_partition_delete_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "resize" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Resize/Move"), this, TQT_SLOT(action_resize_move()) );
			else
				id = m_menu_partition->insertItem( tr("Resize/Move"), this, TQT_SLOT(action_resize_move()) );
		}
		m_menu_partition_resize_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->insertSeparator();
		{
			const TQPixmap pm = load_icon_by_name( "edit-copy" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Copy"), this, TQT_SLOT(action_copy()) );
			else
				id = m_menu_partition->insertItem( tr("Copy"), this, TQT_SLOT(action_copy()) );
		}
		m_menu_partition_copy_id = id;
		m_menu_partition->setItemEnabled( id, false );
		{
			const TQPixmap pm = load_icon_by_name( "edit-paste" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Paste"), this, TQT_SLOT(action_paste()) );
			else
				id = m_menu_partition->insertItem( tr("Paste"), this, TQT_SLOT(action_paste()) );
		}
		m_menu_partition_paste_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->insertSeparator();
		{
			TQPopupMenu *submenu_image = new TQPopupMenu( this );
			id = submenu_image->insertItem( tr("Create Partition Image") + TQString::fromLatin1("..."), this, TQT_SLOT(action_partition_create_image()) );
			m_menu_partition_create_image_id = id;
			submenu_image->setItemEnabled( id, false );
			id = submenu_image->insertItem( tr("Restore Partition Image") + TQString::fromLatin1("..."), this, TQT_SLOT(action_partition_restore_image()) );
			m_menu_partition_restore_image_id = id;
			submenu_image->setItemEnabled( id, false );
			m_menu_partition->insertItem( tr("Image"), submenu_image );
		}
		m_menu_partition->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "sec_erase" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Secure Erase") + TQString::fromLatin1("..."), this, TQT_SLOT(action_partition_secure_erase()) );
			else
				id = m_menu_partition->insertItem( tr("Secure Erase") + TQString::fromLatin1("..."), this, TQT_SLOT(action_partition_secure_erase()) );
		}
		m_menu_partition_secure_erase_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->insertSeparator();
		{
			m_menu_partition_format_to = new TQPopupMenu( this );
			TQObject::connect( m_menu_partition_format_to, TQT_SIGNAL(activated(int)), this, TQT_SLOT(menu_partition_format_to(int)) );
			m_menu_partition_format_to_ids.clear();
			m_menu_partition_format_to_fstypes.clear();
			{
				const std::vector<FS> &fss = m_core.get_filesystems();
				for (unsigned int i = 0; i < fss.size(); i++)
				{
					if (fss[i].create == FS::NONE)
						continue;
					if (fss[i].fstype == FS_UNALLOCATED || fss[i].fstype == FS_UNFORMATTED)
						continue;
					const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( fss[i].fstype ).c_str() );
					const int fid = m_menu_partition_format_to->insertItem( fsname );
					m_menu_partition_format_to_ids.push_back( fid );
					m_menu_partition_format_to_fstypes.push_back( fss[i].fstype );
				}
				{
					const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( FS_CLEARED ).c_str() );
					const int fid = m_menu_partition_format_to->insertItem( fsname );
					m_menu_partition_format_to_ids.push_back( fid );
					m_menu_partition_format_to_fstypes.push_back( FS_CLEARED );
				}
			}
			id = m_menu_partition->insertItem( tr("Format to"), m_menu_partition_format_to );
			m_menu_partition_format_id = id;
			m_menu_partition->setItemEnabled( id, false );
		}
		m_menu_partition->insertSeparator();
		{
			TQPopupMenu *submenu_mount_on = new TQPopupMenu( this );
			m_menu_partition_mount_on = submenu_mount_on;
			TQObject::connect( m_menu_partition_mount_on, TQT_SIGNAL(activated(int)), this, TQT_SLOT(menu_partition_mount_on(int)) );
			m_menu_partition_mount_on_ids.clear();
			m_menu_partition_mount_on_mountpoints.clear();
			id = m_menu_partition->insertItem( tr("Mount on"), m_menu_partition_mount_on );
			m_menu_partition_mount_on_id = id;
			m_menu_partition->setItemEnabled( id, false );
			m_menu_partition->setItemVisible( id, false );
		}
		m_menu_partition->insertSeparator();
		id = m_menu_partition->insertItem( tr("Open Encryption"), this, TQT_SLOT(action_toggle_crypt_busy_state()) );
		m_menu_partition_toggle_crypt_id = id;
		m_menu_partition->setItemEnabled( id, false );
		{
			const TQPixmap pm = mount_icon_pixmap_tqt( false );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("--toggle fs busy--"), this, TQT_SLOT(action_toggle_fs_busy_state()) );
			else
				id = m_menu_partition->insertItem( tr("--toggle fs busy--"), this, TQT_SLOT(action_toggle_fs_busy_state()) );
		}
		m_menu_partition_toggle_fs_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->setItemVisible( id, false );
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "name" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Name Partition"), this, TQT_SLOT(action_name_partition()) );
			else
				id = m_menu_partition->insertItem( tr("Name Partition"), this, TQT_SLOT(action_name_partition()) );
		}
		m_menu_partition_name_id = id;
		m_menu_partition->setItemEnabled( id, false );
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "flag" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Manage Flags"), this, TQT_SLOT(action_manage_flags()) );
			else
				id = m_menu_partition->insertItem( tr("Manage Flags"), this, TQT_SLOT(action_manage_flags()) );
		}
		m_menu_partition_flags_id = id;
		m_menu_partition->setItemEnabled( id, false );
		id = m_menu_partition->insertItem( tr("Check"), this, TQT_SLOT(action_check()) );
		m_menu_partition_check_id = id;
		m_menu_partition->setItemEnabled( id, false );
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "label" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Label File System"), this, TQT_SLOT(action_label_filesystem()) );
			else
				id = m_menu_partition->insertItem( tr("Label File System"), this, TQT_SLOT(action_label_filesystem()) );
		}
		m_menu_partition_label_id = id;
		m_menu_partition->setItemEnabled( id, false );
		id = m_menu_partition->insertItem( tr("New UUID"), this, TQT_SLOT(action_change_uuid()) );
		m_menu_partition_uuid_id = id;
		m_menu_partition->setItemEnabled( id, false );
		m_menu_partition->insertSeparator();
		{
			const TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "info" );
			if (!pm.isNull())
				id = m_menu_partition->insertItem( pm, tr("Information"), this, TQT_SLOT(action_information()) );
			else
				id = m_menu_partition->insertItem( tr("Information"), this, TQT_SLOT(action_information()) );
		}
		m_menu_partition_info_id = id;
		m_menu_partition->setItemEnabled( id, false );
	}
	menuBar()->insertItem( tr("Partition"), m_menu_partition );

	TQPopupMenu *menu_help = new TQPopupMenu( this );
	{
		int id;
		id = menu_help->insertItem( tr("Contents"), this, TQT_SLOT(menu_help_contents()), TQKeySequence("F1") );
		menu_help->setItemEnabled( id, true );
		menu_help->insertSeparator();
		menu_help->insertItem( tr("About"), this, TQT_SLOT(menu_about()) );
	}
	menuBar()->insertItem( tr("Help"), menu_help );
}

void Win_GParted_TQt::menu_view_filesystem_support()
{
	Dialog_Features_TQt dlg( m_core.get_filesystems(), this );
	while (dlg.exec() == TQDialog::Accepted)
	{
		GParted_Core::find_supported_core();
		m_core.find_supported_filesystems();
		dlg.load_filesystems( m_core.get_filesystems() );

		if (m_menu_partition_format_to)
		{
			m_menu_partition_format_to->clear();
			m_menu_partition_format_to_ids.clear();
			m_menu_partition_format_to_fstypes.clear();
			const std::vector<FS> &fss = m_core.get_filesystems();
			for (unsigned int i = 0; i < fss.size(); i++)
			{
				if (fss[i].create == FS::NONE)
					continue;
				if (fss[i].fstype == FS_UNALLOCATED || fss[i].fstype == FS_UNFORMATTED)
					continue;
				const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( fss[i].fstype ).c_str() );
				const int fid = m_menu_partition_format_to->insertItem( fsname );
				m_menu_partition_format_to_ids.push_back( fid );
				m_menu_partition_format_to_fstypes.push_back( fss[i].fstype );
			}
			{
				const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( FS_CLEARED ).c_str() );
				const int fid = m_menu_partition_format_to->insertItem( fsname );
				m_menu_partition_format_to_ids.push_back( fid );
				m_menu_partition_format_to_fstypes.push_back( FS_CLEARED );
			}
		}

		update_valid_actions();
	}
}

void Win_GParted_TQt::menu_help_contents()
{
	try
	{
		Glib::spawn_command_line_async( "tdehelpcenter help:/tdeparted" );
		return;
	}
	catch (...)
	{
	}
	try
	{
		Glib::spawn_command_line_async( "khelpcenter help:/tdeparted" );
		return;
	}
	catch (...)
	{
	}

	TQMessageBox::information(
		this,
		tr("Help"),
		tr("Help is not available in this build."),
		TQMessageBox::Ok,
		TQMessageBox::NoButton,
		TQMessageBox::NoButton
	);
}

void Win_GParted_TQt::init_toolbar()
{
	enum
	{
		TB_REFRESH = 1,
		TB_NEW,
		TB_DELETE,
		TB_RESIZE_MOVE,
		TB_COPY,
		TB_PASTE,
		TB_MOUNT,
		TB_UNDO,
		TB_APPLY,
		TB_DEVICE_BOX
	};

	m_toolbar = new TDEToolBar( this, "main_toolbar", true, true );
	m_toolbar->setLabel( tr("Toolbar") );
	m_toolbar->setIconText( TDEToolBar::IconTextBottom );
	m_toolbar->setIconSize( 32 );
	addToolBar( m_toolbar );

	m_toolbar->insertButton( TQString::fromLatin1("view-refresh"),
	                         TB_REFRESH,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(menu_device_refresh_devices()),
	                         true,
	                         tr("Refresh") );
	m_btn_refresh = m_toolbar->getButton( TB_REFRESH );

	m_toolbar->insertButton( TQString::fromLatin1("document-new"),
	                         TB_NEW,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_new()),
	                         true,
	                         tr("New") );
	m_btn_new = m_toolbar->getButton( TB_NEW );
	if (m_btn_new)
	{
		TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "new" );
		if (!pm.isNull())
		{
			TQIconSet is;
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Normal );
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Active );
			is.setPixmap( make_disabled_pixmap_tqt( pm ), TQIconSet::Automatic, TQIconSet::Disabled );
			m_btn_new->setIconSet( is );
		}
	}

	m_toolbar->insertButton( TQString::fromLatin1("edit-delete"),
	                         TB_DELETE,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_delete()),
	                         true,
	                         tr("Delete") );
	m_btn_delete = m_toolbar->getButton( TB_DELETE );
	if (m_btn_delete)
	{
		TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "delete" );
		if (!pm.isNull())
		{
			TQIconSet is;
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Normal );
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Active );
			is.setPixmap( make_disabled_pixmap_tqt( pm ), TQIconSet::Automatic, TQIconSet::Disabled );
			m_btn_delete->setIconSet( is );
		}
	}

	m_toolbar->insertSeparator();

	m_toolbar->insertButton( TQString::fromLatin1("transform-move"),
	                         TB_RESIZE_MOVE,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_resize_move()),
	                         true,
	                         tr("Resize/Move") );
	m_btn_resize_move = m_toolbar->getButton( TB_RESIZE_MOVE );
	if (m_btn_resize_move)
	{
		TQPixmap pm = load_embedded_ui_icon_by_name_tqt( "resize" );
		if (!pm.isNull())
		{
			TQIconSet is;
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Normal );
			is.setPixmap( pm, TQIconSet::Automatic, TQIconSet::Active );
			is.setPixmap( make_disabled_pixmap_tqt( pm ), TQIconSet::Automatic, TQIconSet::Disabled );
			m_btn_resize_move->setIconSet( is );
		}
	}

	m_toolbar->insertSeparator();

	m_toolbar->insertButton( TQString::fromLatin1("edit-copy"),
	                         TB_COPY,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_copy()),
	                         true,
	                         tr("Copy") );
	m_btn_copy = m_toolbar->getButton( TB_COPY );

	m_toolbar->insertButton( TQString::fromLatin1("edit-paste"),
	                         TB_PASTE,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_paste()),
	                         true,
	                         tr("Paste") );
	m_btn_paste = m_toolbar->getButton( TB_PASTE );

	m_toolbar->insertButton( TQString::fromLatin1(""),
	                         TB_MOUNT,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_toggle_fs_busy_state()),
	                         true,
	                         tr("Mount") );
	m_btn_mount = m_toolbar->getButton( TB_MOUNT );
	if (m_btn_mount)
	{
		set_toolbar_button_iconset_tqt( m_btn_mount, mount_icon_pixmap_tqt( false ) );
		m_btn_mount->setEnabled( false );
	}

	m_toolbar->insertSeparator();

	m_toolbar->insertButton( TQString::fromLatin1("edit-undo"),
	                         TB_UNDO,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_undo()),
	                         true,
	                         tr("Undo") );
	m_btn_undo = m_toolbar->getButton( TB_UNDO );
	if (m_btn_undo)
		m_btn_undo->setEnabled( false );

	m_toolbar->insertButton( TQString::fromLatin1("gtk-execute"),
	                         TB_APPLY,
	                         TQT_SIGNAL(clicked()),
	                         this,
	                         TQT_SLOT(action_apply()),
	                         true,
	                         tr("Apply") );
	m_btn_apply = m_toolbar->getButton( TB_APPLY );
	if (m_btn_apply)
		m_btn_apply->setEnabled( false );

	// Right aligned device selector (grouped to avoid excessive spacing)
	TQWidget *device_box = new TQWidget( m_toolbar );
	{
		TQHBoxLayout *hb = new TQHBoxLayout( device_box );
		hb->setMargin( 0 );
		hb->setSpacing( 6 );
		TQLabel *lbl_device = new TQLabel( tr("Device:"), device_box );
		{
			TQFont f = lbl_device->font();
			f.setBold( true );
			f.setPointSize( f.pointSize() + 2 );
			lbl_device->setFont( f );
		}
		hb->addWidget( lbl_device );

		m_combo_devices = new TQComboBox( false, device_box );
		{
			TQFont f = m_combo_devices->font();
			f.setPointSize( f.pointSize() + 2 );
			m_combo_devices->setFont( f );
		}
		m_combo_devices->setMinimumWidth( 320 );
		m_combo_devices->insertItem( tr("(refreshing devices...)") );
		hb->addWidget( m_combo_devices );
	}
	m_toolbar->insertWidget( TB_DEVICE_BOX, device_box->sizeHint().width(), device_box );
	m_toolbar->alignItemRight( TB_DEVICE_BOX, true );
	TQObject::connect( m_combo_devices, TQT_SIGNAL(activated(int)), this, TQT_SLOT(combo_devices_changed(int)) );
}

void Win_GParted_TQt::refresh_devices()
{
	const Glib::ustring prev_path = (m_current_device >= 0 && m_current_device < (int)m_devices.size())
		? m_devices[m_current_device].get_path()
		: Glib::ustring();

	m_devices.clear();
	delete m_copied_partition;
	m_copied_partition = 0;
	{
		std::vector<Glib::ustring> user_devices = Proc_Partitions_Info::get_device_paths();
		for (unsigned int i = 0; i < m_virtual_attaches.size(); i++)
		{
			const Glib::ustring &p = m_virtual_attaches[i].dev_path;
			if (p.empty())
				continue;
			bool have = false;
			for (unsigned int k = 0; k < user_devices.size(); k++)
			{
				if (user_devices[k] == p)
				{
					have = true;
					break;
				}
			}
			if (!have)
				user_devices.push_back( p );
		}
		m_core.set_user_devices( user_devices );
	}
	m_core.set_devices( m_devices );

	m_combo_devices->clear();
	if (m_menu_gparted_devices)
	{
		m_menu_gparted_devices->clear();
		m_menu_gparted_devices_ids.clear();
	}

	for (unsigned int i = 0; i < m_devices.size(); i++)
	{
		const Device &d = m_devices[i];
		const Glib::ustring size_str = Utils::format_size( d.length, d.sector_size );
		const Glib::ustring label = d.get_path() + " (" + size_str + ")";
		m_combo_devices->insertItem( TQString::fromUtf8( label.c_str() ) );
		if (m_menu_gparted_devices)
		{
			const int mid = m_menu_gparted_devices->insertItem( TQString::fromUtf8( label.c_str() ) );
			m_menu_gparted_devices_ids.push_back( mid );
		}
	}

	if (m_devices.empty())
	{
		m_combo_devices->insertItem( tr("(no devices)") );
		m_current_device = -1;
		m_selected_partition = 0;
		refresh_details_table();
		update_valid_actions();
		return;
	}

	if (m_menu_gparted && m_menu_gparted_devices_id != -1)
		m_menu_gparted->setItemEnabled( m_menu_gparted_devices_id, true );

	int want_idx = 0;
	if (!prev_path.empty())
	{
		for (unsigned int i = 0; i < m_devices.size(); i++)
		{
			if (m_devices[i].get_path() == prev_path)
			{
				want_idx = (int)i;
				break;
			}
		}
	}
	if (want_idx < 0 || want_idx >= (int)m_devices.size())
		want_idx = 0;

	m_combo_devices->setCurrentItem( want_idx );
	combo_devices_changed( want_idx );
}

void Win_GParted_TQt::menu_gparted_devices_select( int id )
{
	int idx = -1;
	for (unsigned int i = 0; i < m_menu_gparted_devices_ids.size(); i++)
	{
		if (m_menu_gparted_devices_ids[i] == id)
		{
			idx = (int)i;
			break;
		}
	}
	if (idx < 0 || idx >= (int)m_devices.size())
		return;
	if (m_combo_devices)
		m_combo_devices->setCurrentItem( idx );
	combo_devices_changed( idx );
}

void Win_GParted_TQt::combo_devices_changed( int index )
{
	if (index < 0 || index >= (int)m_devices.size())
	{
		m_current_device = -1;
		m_selected_partition = 0;
		if (m_details_list)
			m_details_list->clearSelection();
		refresh_details_table();
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->clear();
		return;
	}

	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );

	m_current_device = index;
	if (m_menu_gparted_devices && m_menu_gparted_devices_ids.size() == m_devices.size())
	{
		for (unsigned int i = 0; i < m_devices.size(); i++)
			m_menu_gparted_devices->setItemChecked( m_menu_gparted_devices_ids[i], i == (unsigned int)m_current_device );
	}
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::refresh_visual()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;

	const Glib::ustring sel_path = m_selected_partition_path;
	const Sector sel_s = m_selected_partition_sector_start;
	const Sector sel_e = m_selected_partition_sector_end;
	const int sel_type = m_selected_partition_type;
	const int had_sel = (!sel_path.empty() || sel_s != 0 || sel_e != 0 || sel_type != 0);

	/* m_display_device copy invalidates any pointer into its partitions.
	 * Clear the pointer first, then re-resolve it from stable identifiers. */
	m_selected_partition = 0;

	m_display_device = m_devices[m_current_device];
	for (unsigned int i = 0; i < m_operations.size(); i++)
		if (m_operations[i]->m_device == m_display_device)
			m_operations[i]->apply_to_visual( m_display_device.partitions );

	if (had_sel)
	{
		if (!sel_path.empty())
		{
			for (unsigned int i = 0; i < m_display_device.partitions.size(); i++)
			{
				const Partition &p = m_display_device.partitions[i];
				if (p.get_path() == sel_path)
				{
					m_selected_partition = &m_display_device.partitions[i];
					break;
				}
			}
		}
		if (!m_selected_partition)
		{
			for (unsigned int i = 0; i < m_display_device.partitions.size(); i++)
			{
				const Partition &p = m_display_device.partitions[i];
				if ((int)p.type == sel_type && p.sector_start == sel_s && p.sector_end == sel_e)
				{
					m_selected_partition = &m_display_device.partitions[i];
					break;
				}
			}
		}
		if (!m_selected_partition)
		{
			m_selected_partition_path.clear();
			m_selected_partition_sector_start = 0;
			m_selected_partition_sector_end = 0;
			m_selected_partition_type = 0;
		}
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( m_selected_partition );
	}

	refresh_details_table();
	refresh_device_information();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->load_partitions( m_display_device.partitions, m_display_device.length );
}

void Win_GParted_TQt::details_selection_changed( TQListViewItem *item )
{
	if (m_in_selection_sync)
		return;
	PartitionListViewItem *pit = dynamic_cast<PartitionListViewItem*>( item );
	if (!pit)
		return;
	select_partition_in_details( pit->partition() );
}

void Win_GParted_TQt::details_context_menu( TQListViewItem *item, const TQPoint &pos, int )
{
	if (!m_menu_partition)
		return;
	PartitionListViewItem *pit = dynamic_cast<PartitionListViewItem*>( item );
	if (pit)
	{
		if (pit->partition())
			select_partition_in_details( pit->partition() );
		m_details_list->setSelected( pit, true );
	}
	update_valid_actions();
	m_menu_partition->popup( pos );
}

void Win_GParted_TQt::select_partition_in_details( const Partition *p )
{
	m_selected_partition = p;
	if (p)
	{
		m_selected_partition_path = p->get_path();
		m_selected_partition_sector_start = p->sector_start;
		m_selected_partition_sector_end = p->sector_end;
		m_selected_partition_type = (int)p->type;
	}
	else
	{
		m_selected_partition_path.clear();
		m_selected_partition_sector_start = 0;
		m_selected_partition_sector_end = 0;
		m_selected_partition_type = 0;
	}
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( p );
	update_valid_actions();
}

void Win_GParted_TQt::select_partition_from_visualdisk( const Partition *p )
{
	if (!p || !m_details_list)
		return;
	m_in_selection_sync = 1;
	for (TQListViewItem *it = m_details_list->firstChild(); it; it = it->nextSibling())
	{
		PartitionListViewItem *pit = dynamic_cast<PartitionListViewItem*>( it );
		if (pit && pit->partition() && *pit->partition() == *p)
		{
			m_details_list->setSelected( pit, true );
			m_details_list->ensureItemVisible( pit );
			break;
		}
	}
	m_in_selection_sync = 0;
	select_partition_in_details( p );
}

static bool paste_allowed_tqt( const std::vector<Device> &devices,
	                         int current_device,
	                         const Partition *selected,
	                         const Partition *copied )
{
	if (!selected || !copied)
		return false;
	if (current_device < 0 || current_device >= (int)devices.size())
		return false;

	const bool readonly = devices[current_device].readonly;
	const bool have_device = true;

	const Partition &sel_fsptn = selected->get_filesystem_partition();
	const Partition &copied_fsptn = copied->get_filesystem_partition();

	if (selected->type == TYPE_UNALLOCATED)
	{
		if (readonly)
			return false;
		if (copied->fstype == FS_LUKS)
			return false;

		Byte_Value required_size = 0;
		if (copied_fsptn.fstype == FS_XFS)
			required_size = copied_fsptn.estimated_min_size() * copied_fsptn.sector_size;
		else
			required_size = copied_fsptn.get_byte_length();

		// Reserve a MEBIBYTE at the start of the partition for partition table or EBR.
		if (selected->inside_extended ||
		    selected->sector_start < MEBIBYTE / selected->sector_size)
			required_size += MEBIBYTE;

		// Reserve space for the EBR for a following logical partition.
		if ( ( ( selected->inside_extended && selected->type == TYPE_UNALLOCATED ) ||
		       ( selected->type == TYPE_LOGICAL ) ) &&
		     have_device &&
		     ( selected->sector_end <
		       ( devices[current_device].length - ( 2 * MEBIBYTE / devices[current_device].sector_size ) ) ) )
			required_size += MEBIBYTE;

		// Reserve space for the backup partition table on GPT.
		if ( have_device &&
		     ( devices[current_device].disktype == "gpt" ) &&
		     ( ( devices[current_device].length - selected->sector_end ) <
		       ( MEBIBYTE / devices[current_device].sector_size ) ) )
			required_size += MEBIBYTE;

		if (required_size <= selected->get_byte_length())
			return true;
		return false;
	}

	if (selected->status == STAT_REAL &&
	    copied_fsptn.get_byte_length() <= sel_fsptn.get_byte_length() &&
	    *copied != *selected)
		return true;

	return false;
}

void Win_GParted_TQt::update_valid_actions()
{
	const bool have_device = (m_current_device >= 0 && m_current_device < (int)m_devices.size());
	const bool have_sel = (m_selected_partition != 0);
	const bool readonly = have_device ? m_devices[m_current_device].readonly : true;
	const bool have_ops = (m_operations.size() > 0);
	bool allow_detach_virtual = false;
	if (have_device && !have_ops)
	{
		const Glib::ustring dev_path = m_devices[m_current_device].get_path();
		for (unsigned int i = 0; i < m_virtual_attaches.size(); i++)
		{
			if (m_virtual_attaches[i].dev_path == dev_path)
			{
				allow_detach_virtual = true;
				break;
			}
		}
	}

	bool allow_new = false;
	bool allow_delete = false;
	bool allow_resize = false;
	bool allow_copy = false;
	bool allow_paste = false;
	bool allow_info = false;
	bool allow_format = false;
	bool allow_toggle_crypt = false;
	bool allow_toggle_fs = false;
	bool allow_mount_on = false;
	bool allow_name = false;
	bool allow_flags = false;
	bool allow_check = false;
	bool allow_label = false;
	bool allow_uuid = false;
	TQString toggle_crypt_label = tr("Open Encryption");
	TQString toggle_fs_label = tr("--toggle fs busy--");
	bool toggle_fs_busy = false;

	if (have_sel)
	{
		allow_info = true;
		const Partition &fsptn = m_selected_partition->get_filesystem_partition();
		toggle_fs_busy = fsptn.busy ? true : false;
		const FS &fs_cap = m_core.get_fs( fsptn.fstype );
		const FS &enc_cap = m_core.get_fs( FS_LUKS );

		// Toggle crypt open/close (enabled for LUKS; handler decides open vs close).
		if (m_selected_partition->status == STAT_REAL && m_selected_partition->fstype == FS_LUKS)
			allow_toggle_crypt = true;
		if (m_selected_partition->fstype == FS_LUKS)
		{
			const FileSystem *luks_obj = m_core.get_filesystem_object( FS_LUKS );
			if (luks_obj)
			{
				toggle_crypt_label = strip_gtk_mnemonic_underscores( TQString::fromUtf8( luks_obj->get_custom_text( fsptn.busy ? CTEXT_DEACTIVATE_FILESYSTEM : CTEXT_ACTIVATE_FILESYSTEM ).c_str() ) );
			}
		}

		// Toggle fs busy: Unmount/swapoff/VG deactivate.
		if (m_selected_partition->status == STAT_REAL &&
		    m_selected_partition->type != TYPE_EXTENDED &&
		    fsptn.fstype != FS_LVM2_PV &&
		    fsptn.fstype != FS_LINUX_SWRAID &&
		    fsptn.fstype != FS_ATARAID &&
		    fsptn.fstype != FS_LUKS &&
		    fsptn.fstype != FS_BCACHE &&
		    fsptn.fstype != FS_JBD &&
		    ( fsptn.fstype == FS_LINUX_SWAP || fsptn.busy || ( !fsptn.busy && fsptn.fstype != FS_UNALLOCATED ) ) )
			allow_toggle_fs = true;
		if (m_selected_partition->status == STAT_REAL &&
		    fsptn.fstype == FS_LVM2_PV &&
		    ( fsptn.busy || fsptn.get_mountpoints().size() > 0 ) )
			allow_toggle_fs = true;
		{
			const FileSystem *filesystem_object = m_core.get_filesystem_object( fsptn.fstype );
			if (filesystem_object)
				toggle_fs_label = strip_gtk_mnemonic_underscores( TQString::fromUtf8( filesystem_object->get_custom_text( fsptn.busy ? CTEXT_DEACTIVATE_FILESYSTEM : CTEXT_ACTIVATE_FILESYSTEM ).c_str() ) );
			else
				toggle_fs_label = strip_gtk_mnemonic_underscores( TQString::fromUtf8( FileSystem::get_generic_text( fsptn.busy ? CTEXT_DEACTIVATE_FILESYSTEM : CTEXT_ACTIVATE_FILESYSTEM ).c_str() ) );
		}

		// Online resizing always required the ability to update the partition table ...
		if (!readonly && fsptn.busy)
		{
			if (m_selected_partition->fstype != FS_LUKS && (fs_cap.online_grow || fs_cap.online_shrink))
				allow_resize = true;
			if (m_selected_partition->fstype == FS_LUKS &&
			    m_selected_partition->busy &&
			    ( (enc_cap.online_grow && fs_cap.online_grow) || (enc_cap.online_shrink && fs_cap.online_shrink) ) )
				allow_resize = true;
			if (m_selected_partition->type == TYPE_EXTENDED)
				allow_resize = true;
		}

		// Allow labelling of mounted file systems that support it.
		if (fsptn.busy && m_selected_partition->status == STAT_REAL && fs_cap.online_write_label)
			allow_label = true;

		// Allow partition naming on devices that support it.
		if (m_selected_partition->status == STAT_REAL &&
		    have_device && m_devices[m_current_device].partition_naming_supported() &&
		    (m_selected_partition->type == TYPE_PRIMARY ||
		     m_selected_partition->type == TYPE_LOGICAL ||
		     m_selected_partition->type == TYPE_EXTENDED))
			allow_name = true;

		// Allow partition flag management.
		if (m_selected_partition->status == STAT_REAL &&
		    (m_selected_partition->type == TYPE_PRIMARY ||
		     m_selected_partition->type == TYPE_LOGICAL ||
		     m_selected_partition->type == TYPE_EXTENDED))
			allow_flags = true;

		// Only unmount/swapoff/VG deactivate or online actions allowed if busy
		if (fsptn.busy)
			goto done_selected;

		// UNALLOCATED space within a partition table or UNALLOCATED whole disk device
		if (m_selected_partition->fstype == FS_UNALLOCATED &&
		    m_selected_partition->get_sector_length() >= ( MEBIBYTE / m_selected_partition->sector_size ))
			allow_new = true;

		// UNALLOCATED space within a partition table
		if (m_selected_partition->type == TYPE_UNALLOCATED)
		{
			allow_paste = paste_allowed_tqt( m_devices, m_current_device, m_selected_partition, m_copied_partition );
			goto done_selected;
		}

		// EXTENDED
		if (m_selected_partition->type == TYPE_EXTENDED)
		{
			// Deletion is only allowed when there are no logical partitions inside.
			if (!readonly)
			{
				if (m_selected_partition->logicals.size() == 0)
					allow_delete = true;
				else if (m_selected_partition->logicals.size() == 1 &&
				         m_selected_partition->logicals.back().type == TYPE_UNALLOCATED)
					allow_delete = true;
			}
			if (!readonly)
				allow_resize = true;
			goto done_selected;
		}

		// PRIMARY, LOGICAL and UNPARTITIONED; partitions with supported file system.
		if ( ( m_selected_partition->type == TYPE_PRIMARY ||
		       m_selected_partition->type == TYPE_LOGICAL ||
		       m_selected_partition->type == TYPE_UNPARTITIONED ) &&
		     m_selected_partition->fstype != FS_UNALLOCATED )
		{
			allow_format = true;
			if ( ( m_selected_partition->type == TYPE_PRIMARY || m_selected_partition->type == TYPE_LOGICAL ) &&
			     !m_selected_partition->busy )
				allow_delete = true;
			if (!readonly)
			{
				if (m_selected_partition->fstype != FS_LUKS && (fs_cap.grow || fs_cap.shrink || fs_cap.move))
					allow_resize = true;
				if (m_selected_partition->fstype == FS_LUKS && !m_selected_partition->busy && (enc_cap.grow || enc_cap.move))
					allow_resize = true;
				if (m_selected_partition->fstype == FS_LUKS && m_selected_partition->busy &&
				    ( (enc_cap.online_grow && fs_cap.grow) || (enc_cap.online_shrink && fs_cap.shrink) ) )
					allow_resize = true;
			}

			if (m_selected_partition->status == STAT_REAL && fsptn.fstype != FS_LUKS && fs_cap.copy)
				allow_copy = true;
			if (m_selected_partition->status == STAT_REAL && fs_cap.write_label)
				allow_label = true;
			if (m_selected_partition->status == STAT_REAL && fs_cap.write_uuid)
				allow_uuid = true;
			if (m_selected_partition->status == STAT_REAL && fs_cap.check)
				allow_check = true;

			// Mount on submenu.
			if (fsptn.fstype != FS_LVM2_PV && fsptn.fstype != FS_LUKS && fsptn.get_mountpoints().size() > 0)
				allow_mount_on = true;
		}

		// Offline labelling.
		if (!fsptn.busy && m_selected_partition->status == STAT_REAL && fs_cap.write_label)
			allow_label = true;

		// UUID change only allowed when inactive.
		if (!fsptn.busy && m_selected_partition->status == STAT_REAL && fs_cap.write_uuid)
			allow_uuid = true;

		// Check/repair only when inactive.
		if (!fsptn.busy && m_selected_partition->status == STAT_REAL && fs_cap.check)
			allow_check = true;

		// Single source of truth: paste_allowed_tqt() handles both
		// unallocated (including MiB reservations) and existing partitions,
		// while also matching GTK behaviour on read-only devices.
		if (m_copied_partition)
			allow_paste = paste_allowed_tqt( m_devices, m_current_device, m_selected_partition, m_copied_partition );

		done_selected:
		;
	}

	if (m_menu_partition)
	{
		const bool allow_image_disk = have_device && !have_ops;
		const bool allow_image_part = have_sel && !have_ops;
		if (m_menu_partition_format_to)
		{
			m_menu_partition_format_to->clear();
			m_menu_partition_format_to_ids.clear();
			m_menu_partition_format_to_fstypes.clear();
			const std::vector<FS> &fss = m_core.get_filesystems();
			for (unsigned int i = 0; i < fss.size(); i++)
			{
				if (fss[i].create == FS::NONE)
					continue;
				if (fss[i].fstype == FS_UNALLOCATED || fss[i].fstype == FS_UNFORMATTED)
					continue;
				const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( fss[i].fstype ).c_str() );
				const int fid = m_menu_partition_format_to->insertItem( fsname );
				m_menu_partition_format_to_ids.push_back( fid );
				m_menu_partition_format_to_fstypes.push_back( fss[i].fstype );
			}
			{
				const TQString fsname = TQString::fromUtf8( Utils::get_filesystem_string( FS_CLEARED ).c_str() );
				const int fid = m_menu_partition_format_to->insertItem( fsname );
				m_menu_partition_format_to_ids.push_back( fid );
				m_menu_partition_format_to_fstypes.push_back( FS_CLEARED );
			}
		}
		if (m_menu_device && m_menu_device_create_image_id != -1)
			m_menu_device->setItemEnabled( m_menu_device_create_image_id, allow_image_disk );
		if (m_menu_device && m_menu_device_restore_image_id != -1)
			m_menu_device->setItemEnabled( m_menu_device_restore_image_id, allow_image_disk );
		if (m_menu_partition_create_image_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_create_image_id, allow_image_part );
		if (m_menu_partition_restore_image_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_restore_image_id, allow_image_part );

		if (m_menu_partition_new_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_new_id, allow_new );
		if (m_menu_partition_delete_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_delete_id, allow_delete );
		if (m_menu_partition_resize_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_resize_id, allow_resize );
		if (m_menu_partition_copy_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_copy_id, allow_copy );
		if (m_menu_partition_paste_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_paste_id, allow_paste );
		if (m_menu_partition_format_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_format_id, allow_format );
		if (m_menu_partition_toggle_crypt_id != -1)
		{
			m_menu_partition->changeItem( m_menu_partition_toggle_crypt_id, toggle_crypt_label );
			m_menu_partition->setItemEnabled( m_menu_partition_toggle_crypt_id, allow_toggle_crypt );
		}
		if (m_menu_partition_toggle_fs_id != -1)
		{
			const TQPixmap pm = mount_icon_pixmap_tqt( toggle_fs_busy );
			if (!pm.isNull())
				m_menu_partition->changeItem( pm, toggle_fs_label, m_menu_partition_toggle_fs_id );
			else
				m_menu_partition->changeItem( m_menu_partition_toggle_fs_id, toggle_fs_label );
			m_menu_partition->setItemEnabled( m_menu_partition_toggle_fs_id, allow_toggle_fs );
			m_menu_partition->setItemVisible( m_menu_partition_toggle_fs_id, allow_toggle_fs );
		}
		if (m_menu_partition_mount_on_id != -1)
		{
			m_menu_partition->setItemEnabled( m_menu_partition_mount_on_id, allow_mount_on );
			m_menu_partition->setItemVisible( m_menu_partition_mount_on_id, allow_mount_on );
		}
		if (m_menu_partition_mount_on && allow_mount_on && m_selected_partition)
		{
			m_menu_partition_mount_on->clear();
			m_menu_partition_mount_on_ids.clear();
			m_menu_partition_mount_on_mountpoints.clear();
			const std::vector<Glib::ustring> &mps = m_selected_partition->get_filesystem_partition().get_mountpoints();
			for (unsigned int i = 0; i < mps.size(); i++)
			{
				const int mid = m_menu_partition_mount_on->insertItem( TQString::fromUtf8( mps[i].c_str() ) );
				m_menu_partition_mount_on_ids.push_back( mid );
				m_menu_partition_mount_on_mountpoints.push_back( mps[i] );
			}
		}
		if (m_menu_partition_name_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_name_id, allow_name );
		if (m_menu_partition_flags_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_flags_id, allow_flags );
		if (m_menu_partition_check_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_check_id, allow_check );
		if (m_menu_partition_label_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_label_id, allow_label );
		if (m_menu_partition_uuid_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_uuid_id, allow_uuid );
		if (m_menu_partition_secure_erase_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_secure_erase_id, have_device && !have_ops );
		if (m_menu_partition_info_id != -1)
			m_menu_partition->setItemEnabled( m_menu_partition_info_id, allow_info );
	}

	if (m_btn_new)
		m_btn_new->setEnabled( allow_new );
	if (m_btn_delete)
		m_btn_delete->setEnabled( allow_delete );
	if (m_btn_resize_move)
		m_btn_resize_move->setEnabled( allow_resize );
	if (m_btn_copy)
		m_btn_copy->setEnabled( allow_copy );
	if (m_btn_paste)
		m_btn_paste->setEnabled( allow_paste );
	if (m_btn_mount)
	{
		m_btn_mount->setEnabled( allow_toggle_fs );
		if (allow_toggle_fs && m_selected_partition)
		{
			const Partition &fsptn = m_selected_partition->get_filesystem_partition();
			const bool mounted = fsptn.busy ? true : false;
			set_toolbar_button_iconset_tqt( m_btn_mount, mount_icon_pixmap_tqt( mounted ) );
			m_btn_mount->setTextLabel( mounted ? tr("Unmount") : tr("Mount"), false );
		}
		else
		{
			set_toolbar_button_iconset_tqt( m_btn_mount, mount_icon_pixmap_tqt( false ) );
			m_btn_mount->setTextLabel( tr("Mount"), false );
		}
	}

	if (m_menu_device && m_menu_device_create_table_id != -1)
		m_menu_device->setItemEnabled( m_menu_device_create_table_id, have_device && !have_ops );
	if (m_menu_device && m_menu_device_secure_erase_id != -1)
		m_menu_device->setItemEnabled( m_menu_device_secure_erase_id, have_device && !have_ops );
	if (m_menu_device && m_menu_device_smart_infos_id != -1)
		m_menu_device->setItemEnabled( m_menu_device_smart_infos_id, have_device );
	if (m_menu_device && m_menu_device_simple_benchmark_id != -1)
		m_menu_device->setItemEnabled( m_menu_device_simple_benchmark_id, have_device );
	if (m_menu_device && m_menu_device_detach_virtual_id != -1)
		m_menu_device->setItemEnabled( m_menu_device_detach_virtual_id, allow_detach_virtual );
	if (m_btn_undo)
		m_btn_undo->setEnabled( have_ops );
	if (m_btn_apply)
		m_btn_apply->setEnabled( have_ops );
	if (m_menu_edit)
	{
		if (m_menu_edit_undo_id != -1)
			m_menu_edit->setItemEnabled( m_menu_edit_undo_id, have_ops );
		if (m_menu_edit_clear_id != -1)
			m_menu_edit->setItemEnabled( m_menu_edit_clear_id, have_ops );
		if (m_menu_edit_apply_id != -1)
			m_menu_edit->setItemEnabled( m_menu_edit_apply_id, have_ops );
	}
	if (m_ops_popup)
	{
		if (m_ops_popup_undo_id != -1)
			m_ops_popup->setItemEnabled( m_ops_popup_undo_id, have_ops );
		if (m_ops_popup_clear_id != -1)
			m_ops_popup->setItemEnabled( m_ops_popup_clear_id, have_ops );
		if (m_ops_popup_apply_id != -1)
			m_ops_popup->setItemEnabled( m_ops_popup_apply_id, have_ops );
	}
}

static void show_disklabel_unrecognized_tqt( TQWidget *parent, const Glib::ustring &device_name );

void Win_GParted_TQt::action_new()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (!m_selected_partition)
		return;

	// Unrecognised whole disk device
	if (m_selected_partition->type   == TYPE_UNPARTITIONED &&
	    m_selected_partition->fstype == FS_UNALLOCATED)
	{
		show_disklabel_unrecognized_tqt( this, m_devices[m_current_device].get_path() );
		return;
	}

	if (m_selected_partition->type != TYPE_UNALLOCATED)
		return;

	const Device &d = (m_operations.size() > 0) ? m_display_device : m_devices[m_current_device];
	bool any_extended = false;
	{
		const PartitionVector &pv = d.partitions;
		for (unsigned int i = 0; i < pv.size(); i++)
		{
			if (pv[i].type == TYPE_EXTENDED)
			{
				any_extended = true;
				break;
			}
		}
	}

	Dialog_Partition_New_TQt dlg( d,
	                             *m_selected_partition,
	                             any_extended,
	                             m_new_count,
	                             m_core.get_filesystems(),
	                             this );
	if (dlg.exec() != TQDialog::Accepted)
		return;

	std::unique_ptr<Operation> op = std::make_unique<OperationCreate>(
		m_devices[m_current_device],
		*m_selected_partition,
		dlg.get_new_partition() );
	op->m_icon = load_icon_by_name( "document-new" );
	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	m_new_count++;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

bool Win_GParted_TQt::add_operation( const Device &device, std::unique_ptr<Operation> operation )
{
	if (!operation)
		return false;

	if (operation->m_type == OPERATION_CREATE ||
	    operation->m_type == OPERATION_COPY ||
	    operation->m_type == OPERATION_RESIZE_MOVE)
	{
		Glib::ustring error;
		if (!m_core.valid_partition( device, operation->get_partition_new(), error ))
		{
			TQMessageBox::critical( this,
				tr("Error"),
				tr("Could not add this operation to the list") +
				TQString::fromLatin1("\n\n") +
				TQString::fromUtf8( error.c_str() ),
				TQMessageBox::Ok,
				TQMessageBox::NoButton );
			return false;
		}
	}

	operation->create_description();
	if (merge_operation( *operation ))
		return true;

	m_operations.push_back( std::move(operation) );
	return true;
}

bool Win_GParted_TQt::merge_operation( const Operation &candidate )
{
	for (signed int i = (signed int)m_operations.size() - 1; i >= 0; i--)
	{
		if (operations_affect_same_partition( *m_operations[i], candidate ))
			return m_operations[i]->merge_operations( candidate );
	}
	return false;
}

bool Win_GParted_TQt::operations_affect_same_partition( const Operation &first_op, const Operation &second_op )
{
	if (first_op.m_type == OPERATION_DELETE)
		return false;

	if (first_op.get_partition_new().get_path() == second_op.get_partition_original().get_path())
		return true;

	Glib::ustring first_copied_path;
	if (first_op.m_type == OPERATION_COPY)
	{
		const OperationCopy &first_copy_op = static_cast<const OperationCopy&>( first_op );
		first_copied_path = first_copy_op.get_partition_copied().get_path();
		if (first_copied_path == second_op.get_partition_original().get_path())
			return true;
	}

	Glib::ustring second_copied_path;
	if (second_op.m_type == OPERATION_COPY)
	{
		const OperationCopy &second_copy_op = static_cast<const OperationCopy&>( second_op );
		second_copied_path = second_copy_op.get_partition_copied().get_path();
		if (first_op.get_partition_new().get_path() == second_copied_path)
			return true;
	}

	if (first_op.m_type == OPERATION_COPY && second_op.m_type == OPERATION_COPY)
	{
		if (first_copied_path == second_copied_path)
			return true;
	}

	return false;
}

void Win_GParted_TQt::menu_partition_format_to( int id )
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (!m_selected_partition)
		return;

	int idx = -1;
	for (unsigned int i = 0; i < m_menu_partition_format_to_ids.size(); i++)
	{
		if (m_menu_partition_format_to_ids[i] == id)
		{
			idx = (int)i;
			break;
		}
	}
	if (idx < 0 || idx >= (int)m_menu_partition_format_to_fstypes.size())
		return;

	const FSType new_fs = m_menu_partition_format_to_fstypes[idx];
	const Partition *sel = m_selected_partition;
	const Partition &sel_fsptn = sel->get_filesystem_partition();

	if (sel->type == TYPE_UNALLOCATED)
		return;
	if (sel->status != STAT_REAL)
		return;
	if (sel_fsptn.busy)
		return;

	Partition *temp_ptn = sel->clone();
	{
		Partition &temp_fsptn = temp_ptn->get_filesystem_partition();
		temp_fsptn.Reset();
		temp_fsptn.status = sel_fsptn.status;
		temp_fsptn.Set( sel_fsptn.device_path,
		              sel_fsptn.get_path(),
		              sel_fsptn.partition_number,
		              sel_fsptn.type,
		              new_fs,
		              sel_fsptn.sector_start,
		              sel_fsptn.sector_end,
		              sel_fsptn.sector_size,
		              sel_fsptn.inside_extended,
		              false );
	}
	temp_ptn->name = sel->name;
	temp_ptn->set_flags( sel->get_flags() );
	GParted_Core::compose_partition_flags( *temp_ptn, m_devices[m_current_device].disktype );

	std::unique_ptr<Operation> op = std::make_unique<OperationFormat>(
		m_devices[m_current_device],
		*sel,
		*temp_ptn );
	delete temp_ptn;
	temp_ptn = 0;
	op->m_icon = load_icon_by_name( "document-properties" );
	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_delete()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (!m_selected_partition)
		return;

	const Partition *sel = m_selected_partition;
	if (sel->type != TYPE_PRIMARY && sel->type != TYPE_LOGICAL)
		return;

	// Disallow deletion of logical partition if any higher numbered logical partitions are busy.
	if (sel->type == TYPE_LOGICAL &&
	    sel->status != STAT_NEW &&
	    sel->partition_number < m_devices[m_current_device].highest_busy)
	{
		TQString msg = tr("Unable to delete %1!").arg( TQString::fromUtf8( sel->get_path().c_str() ) );
		TQString sec = tr("Please unmount any logical partitions having a number higher than %1")
			.arg( TQString::number( sel->partition_number ) );
		sec += tr("  Failure to boot is most likely to occur if you move the GNU/Linux partition containing /boot, or if you move the Windows system partition C:.");
		sec += "\n";
		sec += tr("You can learn how to repair the boot configuration in the GParted FAQ.");
		sec += "\nhttps://gparted.org/faq.php\n\n";
		sec += tr("Moving a partition might take a very long time to apply.");
		TQMessageBox::critical( this, tr("Delete"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	// Mounted LVM2 PV protection (minimal parity).
	if (sel->fstype == FS_LVM2_PV && sel->busy)
	{
		TQString msg = tr("Unable to delete %1!").arg( TQString::fromUtf8( sel->get_path().c_str() ) );
		TQString sec = tr("Please unmount this volume group before deleting the physical volume.");
		TQMessageBox::critical( this, tr("Delete"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
		return;
	}

	// If deleting partition on the clipboard, confirm and clear clipboard.
	if (m_copied_partition && sel->get_path() == m_copied_partition->get_path())
	{
		TQString msg = tr("Are you sure you want to delete %1?")
			.arg( TQString::fromUtf8( sel->get_path().c_str() ) );
		TQString sec = tr("After deletion this partition is no longer available for copying.");
		const int r = TQMessageBox::warning( this,
			tr("Delete"),
			msg + "\n\n" + sec,
			TQMessageBox::Cancel,
			TQMessageBox::Ok );
		if (r != TQMessageBox::Ok)
			return;
		delete m_copied_partition;
		m_copied_partition = 0;
	}

	if (sel->status == STAT_NEW)
	{
		// Remove all operations which created/modified this new partition.
		const Glib::ustring path = sel->get_path();
		for (int i = 0; i < (int)m_operations.size(); i++)
		{
			if (m_operations[i]->m_type != OPERATION_DELETE &&
			    m_operations[i]->get_partition_new().get_path() == path)
			{
				m_operations.erase( m_operations.begin() + i );
				i--;
			}
		}
		// Determine lowest possible m_new_count.
		unsigned short max_new = 0;
		for (unsigned int t = 0; t < m_operations.size(); t++)
		{
			if (m_operations[t]->m_type != OPERATION_DELETE &&
			    m_operations[t]->get_partition_new().status == STAT_NEW)
			{
				const int n = m_operations[t]->get_partition_new().partition_number;
				if (n > (int)max_new)
					max_new = (unsigned short)n;
			}
		}
		m_new_count = (unsigned short)(max_new + 1);
	}
	else
	{
		std::unique_ptr<Operation> op = std::make_unique<OperationDelete>(
			m_devices[m_current_device],
			*sel );
		op->m_icon = load_icon_by_name( "edit-delete" );
		if (!add_operation( m_devices[m_current_device], std::move(op) ))
			return;
	}

	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

static void show_resize_readonly_tqt( TQWidget *parent, const Glib::ustring &path )
{
	TQString msg = TQString::fromUtf8( Glib::ustring::compose( "Unable to resize read-only file system %1", path ).c_str() );
	TQString sec = TQString::fromUtf8( "The file system can not be resized while it is mounted read-only.\nEither unmount the file system or remount it read-write." );
	TQMessageBox::information( parent, TQString::fromLatin1("Resize/Move"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
}

static void show_disklabel_unrecognized_tqt( TQWidget *parent, const Glib::ustring &device_name )
{
	TQString msg = TQString::fromUtf8( Glib::ustring::compose( "No partition table found on device %1", device_name ).c_str() );
	TQString sec = TQString::fromUtf8( "A partition table is required before partitions can be added.\nTo create a new partition table choose the menu item:\nDevice --> Create Partition Table." );
	TQMessageBox::information( parent, TQString::fromLatin1("Information"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
}

void Win_GParted_TQt::action_resize_move()
{
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;
	if (!m_selected_partition)
		return;
	if (m_devices[m_current_device].readonly)
		return;

	const Partition *sel = m_selected_partition;
	const Partition &sel_fsptn = sel->get_filesystem_partition();
	if (sel_fsptn.busy && sel_fsptn.fs_readonly && sel_fsptn.fstype != FS_REISERFS)
	{
		show_resize_readonly_tqt( this, sel->get_path() );
		return;
	}

	PartitionVector *display_partitions_ptr = &m_display_device.partitions;
	if (sel->type == TYPE_LOGICAL)
	{
		for (unsigned int i = 0; i < m_display_device.partitions.size(); i++)
			if (m_display_device.partitions[i].type == TYPE_EXTENDED)
			{
				display_partitions_ptr = &m_display_device.partitions[i].logicals;
				break;
			}
	}

	const FSType fstype = sel_fsptn.fstype;
	FS fs_cap = m_core.get_fs( fstype );
	FS_Limits fs_limits = m_core.get_filesystem_limits( fstype, sel_fsptn );

	Partition *working_ptn = sel->clone();
	Dialog_Partition_Resize_Move_TQt dlg( m_display_device,
	                                     fs_cap,
	                                     fs_limits,
	                                     *working_ptn,
	                                     *display_partitions_ptr,
	                                     this );
	delete working_ptn;
	working_ptn = 0;
	if (dlg.exec() != TQDialog::Accepted)
		return;

	Partition *resized_ptn = sel->clone();
	resized_ptn->resize( dlg.get_new_partition() );
	std::unique_ptr<Operation> op = std::make_unique<OperationResizeMove>(
		m_devices[m_current_device],
		*sel,
		*resized_ptn );
	delete resized_ptn;
	resized_ptn = 0;
	op->m_icon = load_icon_by_name( "transform-move" );

	// Warning if moving start sector of real non-extended partition.
	if (op->get_partition_original().status       != STAT_NEW &&
	    op->get_partition_original().sector_start != op->get_partition_new().sector_start &&
	    op->get_partition_original().type         != TYPE_EXTENDED)
	{
		TQString msg = tr("Moving a partition might cause your operating system to fail to boot");
		TQString sec = tr("You have queued an operation to move the start sector of partition %1.")
			.arg( TQString::fromUtf8( op->get_partition_original().get_path().c_str() ) );
		sec += tr("  Failure to boot is most likely to occur if you move the GNU/Linux partition containing /boot, or if you move the Windows system partition C:.");
		sec += "\n";
		sec += tr("You can learn how to repair the boot configuration in the GParted FAQ.");
		sec += "\nhttps://gparted.org/faq.php\n\n";
		sec += tr("Moving a partition might take a very long time to apply.");
		TQMessageBox::warning( this, tr("Resize/Move"), msg + "\n\n" + sec, TQMessageBox::Ok, TQMessageBox::NoButton );
	}

	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_copy()
{
	if (!m_selected_partition)
		return;
	delete m_copied_partition;
	m_copied_partition = m_selected_partition->clone();
	statusBar()->message( tr("Partition copied") );
	update_valid_actions();
}

void Win_GParted_TQt::action_paste()
{
	if (!m_selected_partition || !m_copied_partition)
		return;
	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;

	// Unrecognised whole disk device
	if (m_selected_partition->type   == TYPE_UNPARTITIONED &&
	    m_selected_partition->fstype == FS_UNALLOCATED)
	{
		show_disklabel_unrecognized_tqt( this, m_devices[m_current_device].get_path() );
		return;
	}

	const Partition &copied_fsptn = m_copied_partition->get_filesystem_partition();
	if (!paste_allowed_tqt( m_devices, m_current_device, m_selected_partition, m_copied_partition ))
		return;

	if (m_selected_partition->type == TYPE_UNALLOCATED)
	{
		FS_Limits fs_limits = GParted_Core::get_filesystem_limits( copied_fsptn.fstype, copied_fsptn );
		const FS &fs_cap = m_core.get_fs( copied_fsptn.fstype );

		Partition *part_temp = copied_fsptn.clone();
		part_temp->clear_messages();
		part_temp->clear_mountpoints();
		part_temp->name.clear();

		Dialog_Partition_Copy_TQt dlg( m_devices[m_current_device], fs_cap, fs_limits, *m_selected_partition, *part_temp, this );
		delete part_temp;
		part_temp = 0;

		if (dlg.exec() != TQDialog::Accepted)
			return;

		std::unique_ptr<Operation> op = std::make_unique<OperationCopy>(
			m_devices[m_current_device],
			*m_selected_partition,
			dlg.get_new_partition(),
			*m_copied_partition );
		op->m_icon = load_icon_by_name( "edit-paste" );
		OperationCopy *copy_op = static_cast<OperationCopy*>( op.get() );
		copy_op->get_partition_new().set_path(
			Glib::ustring::compose( "Copy of %1", copy_op->get_partition_copied().get_path() ) );
		if (!add_operation( m_devices[m_current_device], std::move(op) ))
			return;
		refresh_pending_operations_ui();
		m_selected_partition = 0;
		if (m_details_list)
			m_details_list->clearSelection();
		if (m_visualdisk_widget)
			static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
		refresh_visual();
		update_valid_actions();
		return;
	}

	// Pasting into existing partition.
	Partition *partition_new = 0;
	if (m_selected_partition->fstype == FS_LUKS && !m_selected_partition->busy)
	{
		partition_new = new Partition( *m_selected_partition );
	}
	else
	{
		partition_new = m_selected_partition->clone();
	}
	partition_new->alignment = ALIGN_STRICT;
	{
		Partition &filesystem_ptn_new = partition_new->get_filesystem_partition();
		filesystem_ptn_new.fstype = copied_fsptn.fstype;
		filesystem_ptn_new.set_filesystem_label( copied_fsptn.get_filesystem_label() );
		filesystem_ptn_new.uuid = copied_fsptn.uuid;
		const Sector new_size = filesystem_ptn_new.get_sector_length();
		if (copied_fsptn.sector_usage_known())
		{
			if (copied_fsptn.get_sector_length() == new_size)
			{
				filesystem_ptn_new.set_sector_usage(
					copied_fsptn.sectors_used + copied_fsptn.sectors_unused,
					copied_fsptn.sectors_unused );
			}
			else
			{
				filesystem_ptn_new.set_sector_usage(
					new_size,
					new_size - copied_fsptn.sectors_used );
			}
		}
		else
		{
			filesystem_ptn_new.set_sector_usage( -1, -1 );
		}
		filesystem_ptn_new.clear_messages();
	}
	GParted_Core::compose_partition_flags( *partition_new, m_devices[m_current_device].disktype );

	std::unique_ptr<Operation> op = std::make_unique<OperationCopy>(
		m_devices[m_current_device],
		*m_selected_partition,
		*partition_new,
		*m_copied_partition );
	op->m_icon = load_icon_by_name( "edit-paste" );
	delete partition_new;
	partition_new = 0;
	if (!add_operation( m_devices[m_current_device], std::move(op) ))
		return;
	refresh_pending_operations_ui();

	{
		TQString text = tr("You have pasted into an existing partition\nThe data in %1 will be lost if you apply this operation.")
			.arg( TQString::fromUtf8( m_selected_partition->get_path().c_str() ) );
		TQMessageBox::warning( this, tr("Paste"), text, TQMessageBox::Ok, TQMessageBox::NoButton );
	}

	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}
void Win_GParted_TQt::action_undo()
{
	if (m_operations.size() == 0)
		return;
	if (m_operations.back()->m_type == OPERATION_CREATE && m_new_count > 1)
		m_new_count--;
	m_operations.pop_back();
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_clear_operations()
{
	if (m_operations.size() == 0)
		return;
	m_operations.clear();
	refresh_pending_operations_ui();
	m_selected_partition = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_visual();
	update_valid_actions();
}

void Win_GParted_TQt::action_apply()
{
	if (m_operations.size() == 0)
		return;
	const int r = TQMessageBox::warning(
		this,
		tr("Apply"),
		tr("Are you sure you want to apply the pending operations?") + TQString::fromLatin1("\n\n") +
		tr("Editing partitions has the potential to cause LOSS of DATA.") + TQString::fromLatin1("\n") +
		tr("You are advised to backup your data before proceeding."),
		TQMessageBox::Ok,
		TQMessageBox::Cancel,
		TQMessageBox::NoButton );
	if (r != TQMessageBox::Ok)
		return;

	// GTK parity: applying operations is shown in a modal progress dialog.
	// The pending operations pane remains a queue only.
	OperationVector ops_copy;
	for (unsigned int i = 0; i < m_operations.size(); i++)
		ops_copy.push_back( std::move( m_operations[i] ) );
	m_operations.clear();
	refresh_pending_operations_ui();
	update_valid_actions();

	Dialog_Progress_TQt dlg( m_devices, ops_copy, this );
	const bool ok_apply = dlg.run_modal_apply( m_core );

	(void)ok_apply;
	// GTK parity + safety: never restore operations after applying.
	// Some operations may have already been executed before failure/cancel.
	// Always rescan to resync in-memory state with on-disk state.
	m_new_count = 1;
	refresh_devices();
	m_selected_partition = 0;
	m_selected_partition_path.clear();
	m_selected_partition_sector_start = 0;
	m_selected_partition_sector_end = 0;
	m_selected_partition_type = 0;
	if (m_details_list)
		m_details_list->clearSelection();
	if (m_visualdisk_widget)
		static_cast<VisualDiskWidget*>( m_visualdisk_widget )->set_selected( 0 );
	refresh_pending_operations_ui();
	refresh_visual();
	update_window_title();
	update_valid_actions();
}
void Win_GParted_TQt::action_information() { visualdisk_activate_information(); }

static TQString bash_escape_double_quotes_tqt( const TQString &s )
{
	TQString out;
	out.reserve( s.length() + 16 );
	const int n = (int)s.length();
	for (int i = 0; i < n; i++)
	{
		const TQChar c = s[i];
		if (c == '\\')
			out += TQString::fromLatin1("\\\\");
		else if (c == '"')
			out += TQString::fromLatin1("\\\"");
		else if (c == '$')
			out += TQString::fromLatin1("\\$");
		else if (c == '`')
			out += TQString::fromLatin1("\\`");
		else if (c == '!')
			out += TQString::fromLatin1("\\!");
		else if (c == '\n' || c == '\r')
			out += TQString::fromLatin1(" ");
		else
			out += c;
	}
	return out;
}

static TQString format_bytes_to_g_suffix_tqt( uint64_t bytes )
{
	const uint64_t g = bytes / (1024ULL * 1024ULL * 1024ULL);
	if (g == 0)
		return TQString::fromLatin1("1G");
	return TQString::number( (unsigned long long)g ) + TQString::fromLatin1("G");
}

static int ends_with_digit_tqt( const Glib::ustring &s )
{
	if (s.empty())
		return 0;
	const unsigned char c = (unsigned char)s[s.size() - 1];
	return (c >= (unsigned char)'0' && c <= (unsigned char)'9');
}

static TQString build_pending_ops_bash_script_tqt( const OperationVector &ops )
{
	std::vector<Glib::ustring> devs;
	devs.reserve( ops.size() );
	for (unsigned int i = 0; i < ops.size(); i++)
	{
		const Glib::ustring dp = ops[i]->m_device.get_path();
		bool have = false;
		for (unsigned int j = 0; j < devs.size(); j++)
			if (devs[j] == dp)
				have = true;
		if (!have)
			devs.push_back( dp );
	}

	TQString out;
	out += TQString::fromLatin1("#!/bin/bash\n");
	out += TQString::fromLatin1("# Script generated by tdeParted\n");
	out += TQString::fromLatin1("# WARNING: This script will modify disks.\n\n");
	out += TQString::fromLatin1("set -e\n\n");

	if (devs.size() == 1)
	{
		out += TQString::fromLatin1("TARGET_DISK=\"") + TQString::fromUtf8( devs[0].c_str() ) + TQString::fromLatin1("\"\n");
	}
	else
	{
		for (unsigned int i = 0; i < devs.size(); i++)
		{
			out += TQString::fromLatin1("TARGET_DISK_") + TQString::number( (int)i ) + TQString::fromLatin1("=\"") +
			       TQString::fromUtf8( devs[i].c_str() ) + TQString::fromLatin1("\"\n");
		}
	}
	out += TQString::fromLatin1("\n");

	struct PartVar_TQt { Glib::ustring path; int part_num; };
	std::vector<PartVar_TQt> part_paths;
	part_paths.reserve( ops.size() );
	for (unsigned int i = 0; i < ops.size(); i++)
	{
		const Partition &po = ops[i]->get_partition_original();
		const Glib::ustring pp = po.get_path();
		if (pp.empty())
			continue;
		bool have = false;
		for (unsigned int j = 0; j < part_paths.size(); j++)
			if (part_paths[j].path == pp)
				have = true;
		if (!have)
		{
			PartVar_TQt pv;
			pv.path = pp;
			pv.part_num = po.partition_number;
			part_paths.push_back( pv );
		}
	}
	const bool single_disk = (devs.size() == 1);
	const bool single_disk_needs_p = single_disk ? (ends_with_digit_tqt( devs[0] ) != 0) : false;
	for (unsigned int i = 0; i < part_paths.size(); i++)
	{
		out += TQString::fromLatin1("PART_") + TQString::number( (int)(i + 1) ) + TQString::fromLatin1("=\"");
		if (single_disk && part_paths[i].part_num > 0)
		{
			out += TQString::fromLatin1("${TARGET_DISK}");
			if (single_disk_needs_p)
				out += TQString::fromLatin1("p");
			out += TQString::number( part_paths[i].part_num );
		}
		else
		{
			out += TQString::fromUtf8( part_paths[i].path.c_str() );
		}
		out += TQString::fromLatin1("\"\n");
	}
	if (part_paths.size() > 0)
		out += TQString::fromLatin1("\n");

	for (unsigned int i = 0; i < ops.size(); i++)
	{
		const Operation &op = *ops[i];
		out += TQString::fromLatin1("# ") + TQString::fromUtf8( op.m_description.c_str() ) + TQString::fromLatin1("\n");
		const Glib::ustring dev_path = op.m_device.get_path();
		const Partition &po = op.get_partition_original();
		const Glib::ustring ppath = po.get_path();
		int part_var_idx = -1;
		for (unsigned int j = 0; j < part_paths.size(); j++)	if (part_paths[j].path == ppath) part_var_idx = (int)j;
		const TQString part_ref = (part_var_idx >= 0)
			? (TQString::fromLatin1("${PART_") + TQString::number( part_var_idx + 1 ) + TQString::fromLatin1("}"))
			: TQString::fromUtf8( ppath.c_str() );

		switch (op.m_type)
		{
			case OPERATION_DELETE:
				if (po.partition_number > 0)
				{
					out += TQString::fromLatin1("parted -s ");
					out += (devs.size() == 1) ? TQString::fromLatin1("\"$TARGET_DISK\"") : (TQString::fromLatin1("\"") + TQString::fromUtf8( dev_path.c_str() ) + TQString::fromLatin1("\""));
					out += TQString::fromLatin1(" rm ") + TQString::number( po.partition_number ) + TQString::fromLatin1("\n\n");
				}
				else
				{
					out += TQString::fromLatin1("# Unsupported delete target\n\n");
				}
				break;

			case OPERATION_CREATE:
			{
				const Partition &pn = op.get_partition_new();
				if (pn.sector_start > 0 && pn.sector_end > pn.sector_start)
				{
					const TQString fs = TQString::fromUtf8( pn.get_filesystem_string().c_str() );
					out += TQString::fromLatin1("parted -s ");
					out += (devs.size() == 1) ? TQString::fromLatin1("\"$TARGET_DISK\"") : (TQString::fromLatin1("\"") + TQString::fromUtf8( dev_path.c_str() ) + TQString::fromLatin1("\""));
					out += TQString::fromLatin1(" unit s mkpart primary ");
					out += fs + TQString::fromLatin1(" ");
					out += TQString::number( (long long)pn.sector_start ) + TQString::fromLatin1("s ");
					out += TQString::number( (long long)pn.sector_end ) + TQString::fromLatin1("s\n\n");
				}
				else
				{
					out += TQString::fromLatin1("# Unsupported create geometry\n\n");
				}
				break;
			}

			case OPERATION_FORMAT:
			{
				const Partition &pn = op.get_partition_new();
				const TQString fss = TQString::fromUtf8( pn.get_filesystem_string().c_str() );
				const TQString label = pn.filesystem_label_known() ? TQString::fromUtf8( pn.get_filesystem_label().c_str() ) : TQString();
				if (fss == TQString::fromLatin1("ext2") || fss == TQString::fromLatin1("ext3") || fss == TQString::fromLatin1("ext4"))
				{
					out += TQString::fromLatin1("mkfs.") + fss + TQString::fromLatin1(" -F ");
					if (!label.isEmpty())
						out += TQString::fromLatin1("-L \"") + bash_escape_double_quotes_tqt( label ) + TQString::fromLatin1("\" ");
					out += part_ref + TQString::fromLatin1("\n\n");
				}
				else
				{
					out += TQString::fromLatin1("# Unsupported format filesystem: ") + fss + TQString::fromLatin1("\n\n");
				}
				break;
			}

			case OPERATION_RESIZE_MOVE:
			{
				const Partition &pn = op.get_partition_new();
				const Partition &fsp = pn.get_filesystem_partition();
				const TQString fss = TQString::fromUtf8( fsp.get_filesystem_string().c_str() );
				const uint64_t bytes = (uint64_t)pn.get_sector_length() * (uint64_t)pn.sector_size;
				if (fss == TQString::fromLatin1("ext2") || fss == TQString::fromLatin1("ext3") || fss == TQString::fromLatin1("ext4"))
				{
					out += TQString::fromLatin1("e2fsck -f ") + part_ref + TQString::fromLatin1("\n");
					out += TQString::fromLatin1("resize2fs ") + part_ref + TQString::fromLatin1(" ") + format_bytes_to_g_suffix_tqt( bytes ) + TQString::fromLatin1("\n\n");
				}
				else
				{
					out += TQString::fromLatin1("# Unsupported resize filesystem: ") + fss + TQString::fromLatin1("\n\n");
				}
				break;
			}

			default:
				out += TQString::fromLatin1("# Unsupported operation type\n\n");
				break;
		}
	}

	return out;
}

void Win_GParted_TQt::action_export_commands()
{
	if (m_operations.size() == 0)
		return;

	TQDialog dlg( this, 0, true );
	dlg.setCaption( tr("View/export commands") );
	if (!tdeparted_app_icon_pixmap().isNull())
		dlg.setIcon( tdeparted_app_icon_pixmap() );

	TQVBoxLayout *vb = new TQVBoxLayout( &dlg );
	vb->setMargin( 8 );
	vb->setSpacing( 6 );

	TQTextEdit *te = new TQTextEdit( &dlg );
	te->setReadOnly( true );
	te->setTextFormat( TQt::PlainText );
	te->setWordWrap( TQTextEdit::NoWrap );
	te->setText( build_pending_ops_bash_script_tqt( m_operations ) );
	vb->addWidget( te, 1 );

	TQHBoxLayout *hb = new TQHBoxLayout();
	hb->setMargin( 0 );
	hb->setSpacing( 6 );
	hb->addStretch( 1 );
	TQPushButton *btn_copy = new TQPushButton( tr("Copy to clipboard"), &dlg );
	TQPushButton *btn_save = new TQPushButton( tr("Save As...") , &dlg );
	TQPushButton *btn_close = new TQPushButton( tr("Close"), &dlg );
	hb->addWidget( btn_copy );
	hb->addWidget( btn_save );
	hb->addWidget( btn_close );
	vb->addLayout( hb );

	TQObject::connect( btn_close, TQT_SIGNAL(clicked()), &dlg, TQT_SLOT(accept()) );
	TQObject::connect( btn_copy, TQT_SIGNAL(clicked()), te, TQT_SLOT(selectAll()) );
	TQObject::connect( btn_copy, TQT_SIGNAL(clicked()), te, TQT_SLOT(copy()) );

	TQObject::connect( btn_save, TQT_SIGNAL(clicked()), &dlg, TQT_SLOT(reject()) );

	dlg.resize( 900, 650 );
	const int r = dlg.exec();
	if (r == TQDialog::Rejected)
	{
		const TQString filename = TQFileDialog::getSaveFileName(
			TQString(),
			TQString::fromLatin1("Shell Script (*.sh);;All Files (*)"),
			this,
			"save_export_commands",
			tr("Save As") );
		if (filename.isEmpty())
			return;
		std::ofstream out( filename.local8Bit().data() );
		if (!out)
			return;
		out << te->text().local8Bit().data();
		out.close();
	}
}

void Win_GParted_TQt::refresh_pending_operations_ui()
{
	if (m_operations_frame)
	{
		if (m_operations.size() == 0)
			m_operations_frame->hide();
		else
			m_operations_frame->show();
		if (m_menu_view)
			m_menu_view->setItemChecked( m_menu_view_pending_ops_id, m_operations_frame->isVisible() );
	}

	if (m_operations_list)
	{
		m_operations_list->clear();
		for (unsigned int i = 0; i < m_operations.size(); i++)
		{
			TQListViewItem *it = new TQListViewItem( m_operations_list );
			it->setText( 0, TQString::fromUtf8( m_operations[i]->m_description.c_str() ) );
			if (!m_operations[i]->m_icon.isNull())
				it->setPixmap( 0, m_operations[i]->m_icon );
		}
	}
	{
		TQString s;
		s.sprintf( "%u operations pending", (unsigned int)m_operations.size() );
		statusBar()->message( s );
	}
	update_valid_actions();
}

void Win_GParted_TQt::popup_partition_menu_at_cursor()
{
	if (!m_menu_partition)
		return;
	m_menu_partition->popup( TQCursor::pos() );
}

void Win_GParted_TQt::visualdisk_activate_information()
{
	if (!m_selected_partition)
		return;
	Dialog_Partition_Info_TQt dlg( *m_selected_partition, this );
	dlg.exec();
}

void Win_GParted_TQt::refresh_details_table()
{
	m_details_list->clear();

	if (m_current_device < 0 || m_current_device >= (int)m_devices.size())
		return;

	const Device &d = (m_operations.size() > 0) ? m_display_device : m_devices[m_current_device];
	if (m_details_device_label)
	{
		const Glib::ustring size_str = Utils::format_size( d.length, d.sector_size );
		TQString header = TQString::fromUtf8( d.model.c_str() );
		if (!size_str.empty())
			header += TQString::fromLatin1(" - ") + TQString::fromUtf8( size_str.c_str() );
		header += TQString::fromLatin1(" (") + TQString::fromUtf8( d.get_path().c_str() ) + TQString::fromLatin1(")");
		m_details_device_label->setText( header );
	}
	if (m_details_device_icon)
	{
		const TQPixmap &pm = device_type_icon_pixmap_tqt( detect_device_type_tqt( d.get_path() ) );
		if (!pm.isNull())
			m_details_device_icon->setPixmap( pm );
	}
	const PartitionVector &pv = d.partitions;

	for (unsigned int i = 0; i < pv.size(); i++)
	{
		const Partition &p = pv[i];
		if (p.type == TYPE_UNALLOCATED)
		{
			const Glib::ustring size_str = Utils::format_size( p.get_sector_length(), p.sector_size );
			TQListViewItem *item = new PartitionListViewItem(
				&p,
				m_details_list,
				TQString::fromLatin1("unallocated"),
				TQString(),
				TQString(),
				TQString(),
				TQString(),
				TQString::fromUtf8( size_str.c_str() ),
				TQString(),
				TQString()
			);
			item->setPixmap( 2, make_fstype_color_pixmap( FS_UNALLOCATED ) );
			item->setText( 8, TQString() );
			continue;
		}

		const Partition &filesystem_ptn = p.get_filesystem_partition();
		const Glib::ustring path = p.get_path();
		const Glib::ustring name = p.name;
		const Glib::ustring fs = p.get_filesystem_string();
		const Glib::ustring mount = p.get_mountpoint();
		const Glib::ustring label = p.filesystem_label_known() ? p.get_filesystem_label() : "";
		const Glib::ustring size_str = Utils::format_size( p.get_sector_length(), p.sector_size );
		const Glib::ustring used_str = (p.get_sectors_used() == -1) ? "---" : Utils::format_size( p.get_sectors_used(), p.sector_size );
		const Glib::ustring unused_str = (p.get_sectors_unused() == -1) ? "---" : Utils::format_size( p.get_sectors_unused(), p.sector_size );
		Glib::ustring flags_str;
		{
			const std::vector<Glib::ustring> &flags = p.get_flags();
			for (unsigned int fi = 0; fi < flags.size(); fi++)
			{
				if (fi)
					flags_str += ", ";
				flags_str += flags[fi];
			}
		}

		TQListViewItem *item = new PartitionListViewItem(
			&p,
			m_details_list,
			TQString::fromUtf8( path.c_str() ),
			TQString::fromUtf8( name.c_str() ),
			TQString::fromUtf8( fs.c_str() ),
			TQString::fromUtf8( mount.c_str() ),
			TQString::fromUtf8( label.c_str() ),
			TQString::fromUtf8( size_str.c_str() ),
			TQString::fromUtf8( used_str.c_str() ),
			TQString::fromUtf8( unused_str.c_str() )
		);
		item->setText( 8, TQString::fromUtf8( flags_str.c_str() ) );
		item->setPixmap( 2, make_fstype_color_pixmap( filesystem_ptn.fstype ) );
		if (filesystem_ptn.busy)
		{
			const TQPixmap admin = get_admin_pixmap();
			if (!admin.isNull())
				item->setPixmap( 0, admin );
		}
		else if (p.have_messages() > 0)
		{
			const TQPixmap warn = get_warning_pixmap();
			if (!warn.isNull())
				item->setPixmap( 0, warn );
		}
	}
}

void Win_GParted_TQt::init_layout()
{
	m_central_widget = new TQWidget( this );
	setCentralWidget( m_central_widget );

	TQVBoxLayout *vbox = new TQVBoxLayout( m_central_widget );
	vbox->setSpacing( 0 );
	vbox->setMargin( 0 );

	// Visual Disk placeholder (top)
	m_visualdisk_frame = new TQFrame( m_central_widget );
	m_visualdisk_frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
	m_visualdisk_frame->setFixedHeight( 70 + 2 * 5 );
	{
		TQVBoxLayout *vb = new TQVBoxLayout( m_visualdisk_frame );
		vb->setMargin( 0 );
		vb->setSpacing( 0 );
		m_visualdisk_scanning_label = new TQLabel( tr("Scanning devices & partitions..."), m_visualdisk_frame );
		m_visualdisk_scanning_label->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
		vb->addWidget( m_visualdisk_scanning_label, 1 );

		m_visualdisk_widget = new VisualDiskWidget( this, m_visualdisk_frame );
		vb->addWidget( m_visualdisk_widget, 1 );

		m_visualdisk_widget->hide();
		m_visualdisk_scanning_label->show();
	}
	vbox->addWidget( m_visualdisk_frame );

	// Main vertical splitter (middle).  Upper pane: main view.  Lower pane: pending operations (hidden by default).
	m_splitter_v = new TQSplitter( Qt::Vertical, m_central_widget );
	vbox->addWidget( m_splitter_v, 1 );

	// Upper pane: horizontal splitter with optional device info pane on the left.
	m_splitter_h = new TQSplitter( Qt::Horizontal, m_splitter_v );

	m_deviceinfo_frame = new TQFrame( m_splitter_h );
	m_deviceinfo_frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
	{
		TQVBoxLayout *vb = new TQVBoxLayout( m_deviceinfo_frame );
		vb->setMargin( 4 );
		vb->setSpacing( 2 );
		vb->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Device Information") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ) );

		TQGridLayout *grid = new TQGridLayout( vb, 12, 2 );
		grid->setColStretch( 0, 0 );
		grid->setColStretch( 1, 1 );
		grid->setSpacing( 2 );
		grid->setMargin( 0 );

		// Match GTK field order and bold labels.
		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Model:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 0, 0 );
		m_lbl_dev_model = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_model, 0, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Serial:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 1, 0 );
		m_lbl_dev_serial = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_serial, 1, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Device type:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 2, 0 );
		m_lbl_dev_type = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_type, 2, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Size:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 3, 0 );
		m_lbl_dev_size = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_size, 3, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Path:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 4, 0 );
		m_lbl_dev_path = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_path, 4, 1 );

		// Blank separator line.
		grid->addWidget( new TQLabel( TQString(), m_deviceinfo_frame ), 5, 0 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Partition table:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 6, 0 );
		m_lbl_dev_disktype = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_disktype, 6, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Heads:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 7, 0 );
		m_lbl_dev_heads = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_heads, 7, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Sectors/track:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 8, 0 );
		m_lbl_dev_sectors = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_sectors, 8, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Cylinders:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 9, 0 );
		m_lbl_dev_cylinders = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_cylinders, 9, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Total sectors:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 10, 0 );
		m_lbl_dev_total_sectors = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_total_sectors, 10, 1 );

		grid->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Sector size:") + TQString::fromLatin1("</b>"), m_deviceinfo_frame ), 11, 0 );
		m_lbl_dev_sector_size = new TQLabel( m_deviceinfo_frame );
		grid->addWidget( m_lbl_dev_sector_size, 11, 1 );
	}

	// Main details table placeholder (dominant area in GTK UI)
	m_details_frame = new TQFrame( m_splitter_h );
	m_details_frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
	{
		TQVBoxLayout *vb = new TQVBoxLayout( m_details_frame );
		vb->setMargin( 2 );
		vb->setSpacing( 0 );
		m_details_device_header = new TQWidget( m_details_frame );
		{
			TQHBoxLayout *hb = new TQHBoxLayout( m_details_device_header );
			hb->setMargin( 4 );
			hb->setSpacing( 6 );
			m_details_device_icon = new TQLabel( m_details_device_header );
			m_details_device_icon->setFixedSize( 48, 48 );
			m_details_device_icon->setScaledContents( true );
			hb->addWidget( m_details_device_icon );
			m_details_device_label = new TQLabel( m_details_device_header );
			TQFont f = m_details_device_label->font();
			f.setBold( true );
			f.setPointSize( f.pointSize() + 2 );
			m_details_device_label->setFont( f );
			m_details_device_label->setTextFormat( TQt::PlainText );
			hb->addWidget( m_details_device_label, 1 );
		}
		vb->addWidget( m_details_device_header );

		m_details_list = new TQListView( m_details_frame );
		m_details_list->addColumn( tr("Partition") );
		m_details_list->addColumn( tr("Name") );
		m_details_list->addColumn( tr("File System") );
		m_details_list->addColumn( tr("Mount Point") );
		m_details_list->addColumn( tr("Label") );
		m_details_list->addColumn( tr("Size") );
		m_details_list->addColumn( tr("Used") );
		m_details_list->addColumn( tr("Unused") );
		m_details_list->addColumn( tr("Flags") );
		m_details_list->setColumnAlignment( 5, TQt::AlignRight );
		m_details_list->setColumnAlignment( 6, TQt::AlignRight );
		m_details_list->setColumnAlignment( 7, TQt::AlignRight );
		m_details_list->setColumnWidthMode( 0, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 1, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 2, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 3, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 4, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 5, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 6, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 7, TQListView::Maximum );
		m_details_list->setColumnWidthMode( 8, TQListView::Maximum );
		{
			TQFont f = m_details_list->header()->font();
			f.setBold( true );
			m_details_list->header()->setFont( f );
		}
		m_details_list->setAllColumnsShowFocus( true );
		m_details_list->setShowSortIndicator( true );
		m_details_list->setAllColumnsShowFocus( true );
		m_details_list->setRootIsDecorated( false );
		m_details_list->setTreeStepSize( 0 );
		{
			TQFont f = m_details_list->font();
			f.setPointSize( f.pointSize() + 1 );
			m_details_list->setFont( f );
		}
		TQObject::connect( m_details_list, TQT_SIGNAL(selectionChanged(TQListViewItem*)), this, TQT_SLOT(details_selection_changed(TQListViewItem*)) );
		TQObject::connect( m_details_list,
			TQT_SIGNAL(contextMenuRequested(TQListViewItem*,const TQPoint&,int)),
			this,
			TQT_SLOT(details_context_menu(TQListViewItem*,const TQPoint&,int)) );
		vb->addWidget( m_details_list );
	}

	// Match GTK default: device information pane is collapsed/hidden initially.
	m_deviceinfo_frame->hide();
	refresh_device_information();

	// Lower pane: pending operations, hidden by default.
	m_operations_frame = new TQFrame( m_splitter_v );
	m_operations_frame->setFrameStyle( TQFrame::StyledPanel | TQFrame::Sunken );
	m_operations_frame->setMinimumHeight( 100 );
	{
		TQVBoxLayout *vb = new TQVBoxLayout( m_operations_frame );
		vb->setMargin( 2 );
		vb->setSpacing( 2 );
		{
			TQHBoxLayout *hb = new TQHBoxLayout();
			hb->setMargin( 0 );
			hb->setSpacing( 6 );
			hb->addWidget( new TQLabel( TQString::fromLatin1("<b>") + tr("Pending Operations") + TQString::fromLatin1("</b>"), m_operations_frame ), 1 );
			m_btn_export_commands = new TQPushButton( tr("View/export commands"), m_operations_frame );
			hb->addWidget( m_btn_export_commands );
			vb->addLayout( hb );
			TQObject::connect( m_btn_export_commands, TQT_SIGNAL(clicked()), this, TQT_SLOT(action_export_commands()) );
		}

		m_operations_list = new TQListView( m_operations_frame );
		m_operations_list->addColumn( tr("Operation") );
		m_operations_list->setRootIsDecorated( false );
		m_operations_list->setItemMargin( 2 );
		m_operations_list->setAllColumnsShowFocus( true );
		m_operations_list->setSelectionMode( TQListView::NoSelection );
		m_operations_list->setSorting( -1 );
		TQObject::connect( m_operations_list,
			TQT_SIGNAL(contextMenuRequested(TQListViewItem*,const TQPoint&,int)),
			this,
			TQT_SLOT(pending_ops_context_menu(TQListViewItem*,const TQPoint&,int)) );
		vb->addWidget( m_operations_list, 1 );

		m_ops_popup = new TQPopupMenu( this );
		{
			const TQPixmap pm = load_icon_by_name( "edit-undo" );
			if (!pm.isNull())
				m_ops_popup_undo_id = m_ops_popup->insertItem( pm, tr("Undo Last Operation"), this, TQT_SLOT(action_undo()) );
			else
				m_ops_popup_undo_id = m_ops_popup->insertItem( tr("Undo Last Operation"), this, TQT_SLOT(action_undo()) );
		}
		m_ops_popup_clear_id = m_ops_popup->insertItem( tr("Clear All Operations"), this, TQT_SLOT(action_clear_operations()) );
		{
			const TQPixmap pm = load_icon_by_name( "gtk-execute" );
			if (!pm.isNull())
				m_ops_popup_apply_id = m_ops_popup->insertItem( pm, tr("Apply All Operations"), this, TQT_SLOT(action_apply()) );
			else
				m_ops_popup_apply_id = m_ops_popup->insertItem( tr("Apply All Operations"), this, TQT_SLOT(action_apply()) );
		}
		m_ops_popup->insertSeparator();
		m_ops_popup_close_id = m_ops_popup->insertItem( tr("Close"), this, TQT_SLOT(menu_view_pending_operations()) );
	}
	m_operations_frame->hide();
	refresh_pending_operations_ui();

	// Sync view menu check state with default hidden panes.
	if (m_menu_view)
	{
		m_menu_view->setItemChecked( m_menu_view_device_info_id, false );
		m_menu_view->setItemChecked( m_menu_view_pending_ops_id, false );
	}
}

void Win_GParted_TQt::init_statusbar()
{
	statusBar()->message( tr("0 operations pending") );
}

void Win_GParted_TQt::menu_quit()
{
	if (quit_check_operations())
		TQApplication::exit( 0 );
}

bool Win_GParted_TQt::quit_check_operations()
{
	if (m_operations.size() == 0)
		return true;

	TQString msg;
	msg.sprintf( "%u operations are currently pending.", (unsigned int)m_operations.size() );
	const int r = TQMessageBox::warning(
		this,
		tr("Quit"),
		msg,
		TQMessageBox::Ok,
		TQMessageBox::Cancel,
		TQMessageBox::NoButton );
	return r == TQMessageBox::Ok;
}

void Win_GParted_TQt::closeEvent( TQCloseEvent *e )
{
	if (!quit_check_operations())
	{
		e->ignore();
		return;
	}
	if (m_virtual_attaches.empty())
	{
		e->accept();
		return;
	}

	for (unsigned int i = 0; i < m_virtual_attaches.size(); i++)
	{
		const Glib::ustring dev_path = m_virtual_attaches[i].dev_path;
		int didx = -1;
		for (unsigned int di = 0; di < m_devices.size(); di++)
		{
			if (m_devices[di].get_path() == dev_path)
			{
				didx = (int)di;
				break;
			}
		}
		if (didx >= 0)
		{
			if (!ensure_device_unused_tqt( this, m_devices[didx], tr("Detach Virtual Device") ))
			{
				e->ignore();
				return;
			}
		}

	Glib::ustring err;
	if (!virtual_detach_tqt( dev_path, m_virtual_attaches[i].backend, err ))
	{
		TQMessageBox::critical( this, tr("Detach Virtual Device"), tr("Failed to detach virtual device") + TQString::fromLatin1("\n\n") + TQString::fromUtf8( err.c_str() ), TQMessageBox::Ok, TQMessageBox::NoButton );
		e->ignore();
		return;
	}
	}
	m_virtual_attaches.clear();
	e->accept();
}

void Win_GParted_TQt::menu_about()
{
	TQDialog dlg( this, 0, true );
	dlg.setCaption( tr("About") );
	dlg.setFixedSize( 520, 420 );
	if (!tdeparted_app_icon_pixmap().isNull())
		dlg.setIcon( tdeparted_app_icon_pixmap() );
	dlg.setPaletteBackgroundColor( TQColor( "#3e3e3e" ) );

	TQVBoxLayout *v = new TQVBoxLayout( &dlg );
	v->setMargin( 20 );
	v->setSpacing( 14 );

	TQLabel *title = new TQLabel( TQString::fromLatin1("tdeParted"), &dlg );
	{
		TQFont f = title->font();
		f.setBold( true );
		f.setPointSize( f.pointSize() + 6 );
		title->setFont( f );
	}
	title->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	title->setPaletteForegroundColor( TQColor( "#ffffff" ) );
	v->addWidget( title );

	TQLabel *img = new TQLabel( &dlg );
	img->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	img->setPaletteBackgroundColor( TQColor( "#3e3e3e" ) );
	if (!tdeparted_about_pixmap().isNull())
		img->setPixmap( tdeparted_about_pixmap() );
	v->addWidget( img, 0, TQt::AlignHCenter );

	TQLabel *tagline = new TQLabel( TQString::fromLatin1("Trinity DE partition manager"), &dlg );
	{
		TQFont f = tagline->font();
		f.setPointSize( f.pointSize() + 2 );
		tagline->setFont( f );
	}
	tagline->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	tagline->setPaletteForegroundColor( TQColor( "#ffffff" ) );
	v->addWidget( tagline );

	TQLabel *based = new TQLabel( TQString::fromLatin1("based on gparted (https://gparted.org)"), &dlg );
	{
		TQFont f = based->font();
		f.setItalic( true );
		based->setFont( f );
	}
	based->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	based->setPaletteForegroundColor( TQColor( "#ffffff" ) );
	v->addWidget( based );

	TQLabel *author = new TQLabel( TQString::fromLatin1("by seb3773 - https://github.com/seb3773 "), &dlg );
	{
		TQFont fa = author->font();
		TQFont fb = based->font();
		int pa = fa.pointSize();
		if (pa <= 0)
			pa = 10;
		fb.setPointSize( (pa > 1) ? (pa - 1) : pa );
		based->setFont( fb );
	}
	author->setAlignment( TQt::AlignHCenter | TQt::AlignVCenter );
	author->setPaletteForegroundColor( TQColor( "#ffffff" ) );
	v->addWidget( author );

	v->addStretch( 1 );

	TQHBoxLayout *hb = new TQHBoxLayout();
	hb->addStretch( 1 );
	TQPushButton *close = new TQPushButton( tr("Close"), &dlg );
	close->setPaletteForegroundColor( TQColor( "#000000" ) );
	hb->addWidget( close );
	v->addLayout( hb );
	TQObject::connect( close, TQT_SIGNAL(clicked()), &dlg, TQT_SLOT(accept()) );

	dlg.exec();
}

void Win_GParted_TQt::menu_view_device_information()
{
	if (!m_deviceinfo_frame)
		return;

	const bool currently_visible = m_deviceinfo_frame->isVisible();
	if (currently_visible)
		m_deviceinfo_frame->hide();
	else
		m_deviceinfo_frame->show();

	if (m_menu_view)
		m_menu_view->setItemChecked( m_menu_view_device_info_id, m_deviceinfo_frame->isVisible() );
}

void Win_GParted_TQt::menu_view_pending_operations()
{
	if (!m_operations_frame)
		return;

	const bool currently_visible = m_operations_frame->isVisible();
	if (currently_visible)
		m_operations_frame->hide();
	else
		m_operations_frame->show();

	if (m_menu_view)
		m_menu_view->setItemChecked( m_menu_view_pending_ops_id, m_operations_frame->isVisible() );
}

void Win_GParted_TQt::pending_ops_context_menu( TQListViewItem *, const TQPoint &pos, int )
{
	if (!m_ops_popup)
		return;
	update_valid_actions();
	m_ops_popup->popup( pos );
}

void Win_GParted_TQt::menu_device_refresh_devices()
{
	start_initial_scan();
}

}  // namespace GParted
