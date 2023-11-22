#include "mjis_imagelibconnect.h"
#include "mjis_configui.h"


ImageLibConnect::ImageLibConnect(QObject *parent)
	: QObject(parent)
{

}

ImageLibConnect::~ImageLibConnect()
{

}


//二值化参数界面
mjlib::ImageBinaryzation* ImageLibConnect::CreateBinary(bool show)
{
	std::shared_ptr<BinaryImageui> process(new BinaryImageui);
	process->exec();
	return  process->ReturnBinary();
}


//均值滤波参数界面
mjlib::ImageMeanFilter* ImageLibConnect::CreateMean(bool show)
{
	std::shared_ptr<Mean> process(new Mean);
	process->exec();
	return process->ReturnMean();
}



//高斯滤波参数界面
mjlib::ImageGaussianFilter* ImageLibConnect::CreateGaussian(bool show)
{
	std::shared_ptr<Gaussian> process(new Gaussian);
	process->exec();
	return process->ReturnGaussian();
}


//中值滤波参数界面
mjlib::ImageMedianFilter* ImageLibConnect::CreateMedian(bool show)
{
	std::shared_ptr<Median> process(new Median);
	process->exec();
	return process->ReturnMedian();
}



//双边滤波参数界面
mjlib::ImageBilateralFilter* ImageLibConnect::CreateBilateral(bool show)
{
	std::shared_ptr<Bilateral> process(new Bilateral);
	process->exec();
	return process->ReturnBilateral();
}