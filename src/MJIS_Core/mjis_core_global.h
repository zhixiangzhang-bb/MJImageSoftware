#pragma once


#include "mjlib_vision_api.h"
#include "mjis_imageprocess_api.h"
#include <QObject>


//定义谷歌日志库
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif


#if defined(MJIS_Core)
#  define MJIS_Core_API Q_DECL_EXPORT
#else
#  define MJIS_Core_API Q_DECL_IMPORT
#endif

