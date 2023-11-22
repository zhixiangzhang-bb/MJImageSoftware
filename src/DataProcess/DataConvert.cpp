#include "DataConvert.h"

DataConvertManage::DataConvertManage(QObject* parent) :
	QObject(parent)
{
}


DataConvertManage::~DataConvertManage()
{

}


DataConvertManage::DataConvertManage(QString path) 
{
	this->path = path;
}


//转换读到的数据
void DataConvertManage::ConverReadData(const QByteArray& byteArray)
{
	QDataStream stream(byteArray);	
	stream.setByteOrder(QDataStream::BigEndian); // 设置字节顺序为大端字节顺序
	for (size_t i = 0; i < DataStyleList.size(); i++)
	{
		VlaueList[i]=SelectDataStye(static_cast<DataStyle>(DataStyleList[i]), stream, &ByteOrderList[i]);
	}
	emit ReadData();
}



//打开配置文件
void DataConvertManage::OpenConfigurationFiles(const QString& path)
{
	//创建 QSettings 对象并指定配置文件路径
	QSettings settings(path, QSettings::IniFormat);
}

	

//读取配置文件
void DataConvertManage::ReadConfigurationFiles()
{
	QSettings SetFile(path, QSettings::IniFormat);
	//单位列表
	QVector<QString> NamestrList;
	ConfigControl::ReadIniList(SetFile, "name", NamestrList);
	int num = NamestrList.size();
	NameList.resize(num);
	for (size_t i = 0; i < num; i++)
	{
		if (NameList[i] == nullptr) {
			NameList[i] = new QCheckBox(NamestrList[i]);
		}
		else {
			NameList[i]->setText(NamestrList[i]);
		}
	}
	ConfigControl::ReadIniList(SetFile,"datastyle", DataStyleList);
	ConfigControl::ReadIniList(SetFile, "byteorder", ByteOrderList);
	ConfigControl::ReadIniList(SetFile, "unit",UintList);
	VlaueList.resize(DataStyleList.size());
}



//选择数据类型
QString DataConvertManage::SelectDataStye(const DataStyle ds, QDataStream& stream,bool ByteOrder)
{
	switch (ds)
	{
	case DataConvertManage::Bool:
		return 0;
		break;
	case DataConvertManage::Int:
		qint16 intValue;
		stream.readRawData(reinterpret_cast<char*>(&intValue), sizeof(qint16));
		if (ByteOrder) {
			intValue = qFromBigEndian(intValue);
		}
		return QString::number(intValue);
	case DataConvertManage::Float:
		float floatValue;
		stream.readRawData(reinterpret_cast<char*>(&floatValue), sizeof(float));
		if (ByteOrder) {
			floatValue = qFromBigEndian(floatValue);
		}
		return QString::number(floatValue,'f',2);
	default:
		return 0;
		break;
	}
}

//
QVector<QCheckBox*> DataConvertManage::ReturnNameList()
{
	return NameList;
}


QVector<QString> DataConvertManage::ReturnUintList()
{
	return UintList;
}


QVector<QString> DataConvertManage::ReturnVlaueList()
{
	return VlaueList;
}

