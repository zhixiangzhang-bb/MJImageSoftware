#pragma once

#include <QtCore/qglobal.h>



//预定义宏，如果使用了Q_OBJECT宏的话需要先生产moc文件在注释化宏
#if defined(MJIS_HMI)
#  define MJIS_HMI_API Q_DECL_EXPORT
#else
#  define MJIS_HMI_API Q_DECL_IMPORT
#endif
