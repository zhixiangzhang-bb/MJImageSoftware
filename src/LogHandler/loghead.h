#pragma once


#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif