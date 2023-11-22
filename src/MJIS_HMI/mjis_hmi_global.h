#pragma once

#include <QtCore/qglobal.h>


#if defined(MJIS_HMI)
#  define MJIS_HMI_API Q_DECL_EXPORT
#else
#  define MJIS_HMI_API 
#endif
