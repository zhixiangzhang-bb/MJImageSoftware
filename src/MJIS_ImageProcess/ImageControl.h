#pragma once

#include <QObject>
#include <QImage>
#include <QStack>
#include "imagefileio.h"
#include "FeatureExtraction.h"
#include "dockvideo.h"
#include "ImageStatistics.h"
#include <QMessageBox>
#include <QFileDialog>
#include "processinginterface.h"


#if defined(zzxlib_ImageProcess)
#  define ImageControl_EXPORT Q_DECL_EXPORT
#else
#  define ImageControl_EXPORT Q_DECL_IMPORT
#endif


class ImageControl_EXPORT ImageControl  : public QObject
{
	Q_OBJECT

public:
	ImageControl();

	ImageControl(std::shared_ptr<MyDockWidget> dock);

	~ImageControl();

	//打开图片
	MyDockWidget* OpenImage(std::string& path);

	//打开图片
	MyDockWidget* ReturnDock();

	//图像处理
	void ImageProcessResult(ImageProcess* process);

	//统计学
	QVector<QVector<double>> StatisticsImage(ImageStatistics* statistics);

	//处理过程回退
	void PopProcess();

	//处理过程恢复
	void PushProcess();

	//保存最后的图像
	void SaveImage(std::string path);

	//返回图像处理界面
	ProcessingInterface* ReturnInterface();


private:
	//流程显示界面
	std::shared_ptr<ProcessingInterface> pcif;

	//原图片窗口
	std::shared_ptr<MyDockWidget> dock;

	//图像处理前进栈
	QStack<cv::Mat> ProcessAdvanceStack;

	//图像处理类型前进栈
	QStack<int> ProcessNameAdvanceStack;

	//图像处理回退栈
	QStack<cv::Mat> ProcessBackStack;

	//图片转换
	QImage MatImageToQt(cv::Mat src);

};
