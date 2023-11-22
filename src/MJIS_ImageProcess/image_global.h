#pragma once


#include <QtCore/QtGlobal>

#if defined(ImageProcessLib)
#  define LocalCamera_EXPORT Q_DECL_EXPORT
#else
#  define LocalCamera_EXPORT Q_DECL_IMPORT
#endif
