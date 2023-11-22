#pragma once
#define GLOG_NO_ABBREVIATED_SEVERITIES  // 定义宏来禁用缩写的日志严重性宏


#include <glog/logging.h>
#include <QPlainTextEdit>
#include <QDateTime>



class LogHandler:public google::LogSink
{
public:
	//重写日志消息流
	void send(google::LogSeverity severity, const char* full_filename, const char* base_filename,
		int line, const struct ::tm* tm_time, const char* message, size_t message_len) override;

	//创建消息显示列表
	QPlainTextEdit* CreateText();

			
private:
	//消息日志显示文本
	std::shared_ptr<QPlainTextEdit> logTextEdit;

};

