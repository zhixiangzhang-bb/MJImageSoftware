#pragma once


#include "mjis_configui.h"



class MJIS_ImageProcess_API  ImageLibConnect  : public QObject
{
	Q_OBJECT

public:

	ImageLibConnect(QObject *parent);


	~ImageLibConnect();

	//二值化参数界面
	static mjlib::ImageBinaryzation* CreateBinary(bool show);

	//均值滤波参数界面
	static mjlib::ImageMeanFilter* CreateMean(bool show);

	//高斯滤波参数界面
	static mjlib::ImageGaussianFilter* CreateGaussian(bool show);

	//中值滤波参数界面
	static mjlib::ImageMedianFilter* CreateMedian(bool show);

	//双边滤波参数界面
	static mjlib::ImageBilateralFilter* CreateBilateral(bool show);

};
