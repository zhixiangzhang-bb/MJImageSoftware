#pragma once

#include <QObject>
#include <QCoreApplication>
#include "datainterface.h"

#if defined(zzxlib_DataProcess)
#  define DataCommumication_EXPORT Q_DECL_EXPORT
#else
#  define DataCommumication_EXPORT Q_DECL_IMPORT
#endif



/*****************************************************************
* 类名称：数据通讯接口类
* 功能描述：包含一些静态函数，接口等信息，做为库的进出口
* 作者：zzx
* 创建日期：2023.7.31
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



class DataCommumication_EXPORT DataCommumication  : public QObject
{
	Q_OBJECT

public:

	DataCommumication(QObject *parent=nullptr);

	~DataCommumication();

	//测试设备连接
	static bool Ping(const char* ipAddress);

	//返回数据界面
	DataInterface* ReturnUI();

	//写入数据接口
	void WirteDataPort();

	//返回选择的数据
	std::string* ReturnDataSting();

private:
	//UI界面指针
	std::shared_ptr<DataInterface> DatIf;


	//浮点数据接口
	QVector<float>  FloatDataPort;

	//整形数据接口
	QVector<int>  IntDataPort;

	//整形数据接口
	QVector<bool>  BoolDataPort;


};

