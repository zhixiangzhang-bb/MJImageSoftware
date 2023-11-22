#pragma once

#include <QObject>
#include <QMutex>
#include <QImage>
#include "imagefileio.h"



/*****************************************************************
* 类名称：图像管理类
* 功能描述：实现图像处理流程
* 作者：zzx
* 创建日期：2023.6.30
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/


#if defined(ImageProcessLib)
#  define ImageProcessManage_EXPORT Q_DECL_EXPORT
#else
#  define ImageProcessManage_EXPORT Q_DECL_IMPORT
#endif


class ImageProcessManage_EXPORT ImageProcessManage  : public QObject
{
	Q_OBJECT

public:
	explicit  ImageProcessManage(QObject *parent = nullptr);

	explicit  ImageProcessManage(std::string* title, std::string* data);

	~ImageProcessManage();

	//读取图像进图像处理环境
	void ReadQImage(cv::Mat& image);
	
	//图像处理接口进队列里
	void PushImageProcess(ImageProcess* process);

	//图像处理接口出队列
	void BackImageProcess(ImageProcess* process);

	//文件I/O进队列
	void PushImageFile(ImageProcess* process);

	//文件I/O出队列
	void BackImageFile(ImageProcess* process);

	//设置文字格式
	void SetFont(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//设置字幕文本
	void SetTitle(std::string* title, std::string* data);

	//设置相机字幕状态
	void SetTitleCuValue(bool cu);

	//获取相机字幕状态
	bool TitleCuValue();



private:
	QVector<ImageProcess*> ProcessQueue;

	//文件队列,他妈的不想管理内存，这里用智能指针
	QVector<ImageProcess*> FileQueue;

	QMutex mutex;

	//字幕类，本身也是重写图像处理基类，目前先交作业,应该还有优化空间
	std::shared_ptr<ImageSubTitle> subtitle;

	//执行图像处理流程
	void ImageProcessExecute(cv::Mat& image);

	//执行文件I/O流程
	void ImageFileExecute(cv::Mat& image);

	//执行字幕叠加流程
	void ImageSubTitleExecute(cv::Mat& image);

	//转成QT能识别的图像类型
	QImage MatImageToQt(cv::Mat src);

	//字幕控制状态
	bool titlecu;





signals:
	void ReturnProcessImage(QImage& image);
};
