#pragma once

#include <QtCore/qglobal.h>




#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif



//预定义宏，如果使用了Q_OBJECT宏的话需要先生产moc文件在注释化宏
#if defined(MJIS_HMI)
#  define MJIS_HMI_API Q_DECL_EXPORT
#else
#  define MJIS_HMI_API Q_DECL_IMPORT
#endif
