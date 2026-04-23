#ifndef GPARTED_I18N_H
#define GPARTED_I18N_H

	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif /* HAVE_CONFIG_H */
	
	#ifdef ENABLE_NLS
		#include <glibmm/i18n.h>
	#else
		#ifndef _
			#define _(String) (String)
		#endif
	#endif /* ENABLE_NLS */

#endif /* GPARTED_I18N_H */
