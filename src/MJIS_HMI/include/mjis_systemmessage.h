#ifndef SYSTEMMESSAGE_H
#define SYSTEMMESSAGE_H


#define GLOG_NO_ABBREVIATED_SEVERITIES  // 定义宏来禁用缩写的日志严重性宏


#include <QWidget>
#include <QDateTime>
#include <QPlainTextEdit>
#include "mjis_hmi_global.h"

namespace Ui {
	class SystemMessage;
}

namespace mjis {

	namespace hmi {


		/*****************************************************************
		* 类名称：日志消息类
		* 功能描述：继承日志消息流并重写
		* 作者：zzx
		* 创建日期：2023.7.10
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class LogHandler :public google::LogSink
		{
		public:
			//重写日志消息流
			void send(google::LogSeverity severity, const char* full_filename, const char* base_filename,
				int line, const struct ::tm* tm_time, const char* message, size_t message_len) override;

			//创建消息显示列表
			QPlainTextEdit* CreateText();

			//返回消息显示列表
			QPlainTextEdit* ReturnText();


		private:
			//消息日志显示文本
			std::shared_ptr<QPlainTextEdit> logTextEdit;

		};




		/*****************************************************************
		* 类名称：日志显示类
		* 功能描述：显示消息类型
		* 作者：zzx
		* 创建日期：2023.7.10
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/




		class SystemMessage : public QWidget
		{
			Q_OBJECT

		public:
			explicit SystemMessage(QWidget* parent = nullptr);
			~SystemMessage();

		private:
			//日志消息类
			std::shared_ptr<LogHandler> MessageLogging;

			Ui::SystemMessage* ui;
		};

	}
}
#endif // SYSTEMMESSAGE_H
