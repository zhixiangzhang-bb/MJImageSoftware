#pragma once

#include <QObject>
#include <QtEndian>
#include <QIODevice>
#include <QDataStream>
#include <QSettings>
#include <QCheckBox>
#include "mjis_network_global.h"


/*****************************************************************
* 类名称：字节转换类
* 功能描述：提供各种数据类型和字节数组互转的功能
* 作者：zzx
* 创建日期：2023.8.3
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



class DataConvert  : public QObject
{
	Q_OBJECT

public:
	DataConvert(QObject *parent) : QObject(parent){}

	~DataConvert(){}


	//字节流转浮点(大端排列）
	static double  Byte2DoubleBig(const QByteArray& byteArray) 
	{
		if (byteArray.size() == sizeof(float)) {
			float floatValue;
			memcpy(&floatValue, byteArray.constData(), sizeof(float));
			return qFromBigEndian(floatValue);
		}
		else {
			return 0.0;
		}
	}


	//字节流转浮点(小端排列）
	static double  Byte2DoubleLittle(const QByteArray& byteArray)
	{
		if (byteArray.size() == sizeof(float)) {
			float floatValue;
			memcpy(&floatValue, byteArray.constData(), sizeof(float));
			return qFromLittleEndian(floatValue);
		}
		else {
			return 0.0;
		}
	}



	//字节流转整形(大端排列）
	static qint16  Byte2IntBig(const QByteArray& byteArray)
	{
		if (byteArray.size() == sizeof(qint16)) {
			qint16 Value;
			memcpy(&Value, byteArray.constData(), sizeof(qint16));
			return qFromBigEndian(Value);
		}
		else {
			return 0;
		}
	}


	//字节流转整形(小端排列）
	static qint16  Byte2IntLittle(const QByteArray& byteArray)
	{
		if (byteArray.size() == sizeof(qint16)) {
			qint16 Value;
			memcpy(&Value, byteArray.constData(), sizeof(qint16));
			return qFromLittleEndian(Value);
		}
		else {
			return 0;
		}
	}


	//浮点转字节
	static QByteArray  Double2Byte(const double& data)
	{
		float floatValue = static_cast<float>(data);  // 转换为单精度浮点数
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&data), sizeof(floatValue));
	}



	//整形转字节
	static QByteArray  Double2Byte(const int& data)
	{
		return QByteArray::number(data);
	}

};




/*****************************************************************
* 类名称：配置文件类
* 功能描述：提供写入和读取配置的类
* 作者：zzx
* 创建日期：2023.8.4
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class ConfigControl : public QObject
{
	Q_OBJECT

public:
	ConfigControl(QObject* parent = nullptr) {}

	~ConfigControl(){}

	//写入列表到配置文件
	template<typename T>
	static void WriteIniList(QSettings& settings, const QString& name,  QVector<T>& arry)
	{
		// 连接名称存配置文件
		settings.beginWriteArray(name);
		for (int i = 0; i < arry.size(); ++i) {
			settings.setArrayIndex(i);
			settings.setValue("value", arry.at(i));
		}
		settings.endArray();
	}



	//读取配置文件列表
	template<typename T>
	static void ReadIniList(QSettings& settings, const QString& name, QVector<T>& arry)
	{
		int size = settings.beginReadArray(name);
		arry.clear();
		for (int i = 0; i < size; ++i) {
			settings.setArrayIndex(i);
			T value = settings.value("value").value<T>();
			arry.append(value);
		}
		settings.endArray();
	}


private:


};




/*****************************************************************
* 类名称：转换管理类
* 功能描述：调度各类数据读取写入，需要和通讯类配合
* 作者：zzx
* 创建日期：2023.8.4
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



class DataConvertManage : public QObject
{
	Q_OBJECT

public:

	//数据选择类型
	enum DataStyle
	{
		Float,
		Int,
		Bool
	};


	DataConvertManage(QObject* parent=nullptr);

	DataConvertManage(QString path);

	~DataConvertManage();

	//转换读到的数据
	void ConverReadData(const QByteArray& byteArray);

	//打开配置文件
	void OpenConfigurationFiles(const QString& path);

	//读取配置文件数据类型
	void ReadConfigurationFiles();

	//返回名称列表
	QVector<QCheckBox*> ReturnNameList();

	//返回单位列表
	QVector<QString> ReturnUintList();

	//返回值列表
	QVector<QString> ReturnVlaueList();

private:
	QString path;

	//数据类型列表
	QVector<int> DataStyleList;

	//字节顺序列表
	QVector<int> ByteOrderList;

	//复选列表
	QVector<QCheckBox*> NameList;

	//单位列表
	QVector<QString> UintList;

	//数据列表
	QVector<QString> VlaueList;

	//选择数据类型
	QString SelectDataStye(const DataStyle ds, QDataStream& stream, bool ByteOrder);

signals:
	//返回数据列表
	void ReadData();

};


