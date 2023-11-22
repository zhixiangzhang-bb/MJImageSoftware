#include "LogHandler.h"




void LogHandler::send(google::LogSeverity severity, const char* full_filename, const char* base_filename,
	int line, const struct ::tm* tm_time, const char* message, size_t message_len)
{
    Q_UNUSED(full_filename);
    Q_UNUSED(base_filename);
    Q_UNUSED(line);
    Q_UNUSED(tm_time);

    QString logMessage = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss   ")+QString::fromUtf8(message, static_cast<int>(message_len));

    // 根据日志级别设置Qt的文本颜色
    switch (severity) {
    case google::GLOG_INFO:
        // 设置Info级别的日志颜色
        logMessage = "<font color=\"blue\">" + logMessage + "</font>";
        break;
    case google::GLOG_WARNING:
        // 设置Warning级别的日志颜色
        logMessage = "<font color=\"orange\">" + logMessage + "</font>";
        break;
    case google::GLOG_ERROR:
        // 设置Error级别的日志颜色
        logMessage = "<font color=\"red\">" + logMessage + "</font>";
        break;
    case google::GLOG_FATAL:
        // 设置Fatal级别的日志颜色
        logMessage = "<font color=\"red\"><b>" + logMessage + "</b></font>";
        break;
    default:
        break;
    }

    // 将日志消息显示在Qt的文本编辑器中
    logTextEdit->appendHtml(logMessage);
}





QPlainTextEdit* LogHandler::CreateText()
{
    logTextEdit = std::make_shared<QPlainTextEdit>();
    logTextEdit->setFont(QFont("Microsoft YaHei UI", 9));
    logTextEdit->setReadOnly(true);
    return logTextEdit.get();
}