#include "imageprocess.h"
#include <opencv2/freetype.hpp>


ImageProcess::ImageProcess() 
{

}




/*
字幕显示类


*/



ImageSubTitle::ImageSubTitle(std::string* title, std::string* data) :offsetx(50), offsety(50), cR(255), cG(0), cB(0), fontheight(10), fontpath("C:/Windows/Fonts/simsun.ttc"), title(title), data(data)
{

}



//设置字体格式	
void ImageSubTitle::SetFontParam(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)
{
	this->offsetx = offsetx;
	this->offsety = offsety;
	this->cR = cR;
	this->cG = cG;
	this->cB = cB;
	this->fontheight = fontheight;
}


//设置文本，分为标题和数据，共享内存的方式
void ImageSubTitle::SetTitle(std::string* title, std::string* data)
{
	this->title = title;
	this->data = data;
}


//叠加字幕的处理方式
cv::Mat ImageSubTitle::processImage(const cv::Mat& image)
{
	cv::Ptr<cv::freetype::FreeType2> font;
	font = cv::freetype::createFreeType2();
	font->loadFontData(fontpath, 0);
	std::string str;
	if (title == nullptr && data == nullptr) {
		str = "";
	}
	else if (title == nullptr) {
		str = *data;
	}
	else if (data == nullptr) {
		str = *title;
	}
	else {
		str = *title + "\n" + *data;
	}

	int x = this->offsetx;
	int y = this->offsety;
	int lineSpacing = 10; // 行间距
	std::istringstream iss(str);
	std::string line;
	while (std::getline(iss, line)) {
		cv::Size textSize;
		int baseline;
		textSize = font->getTextSize(line, fontheight, 0, &baseline);
		font->putText(image, line, cv::Point(x, y), fontheight, cv::Scalar(cB, cG, cR), cv::FILLED, cv::LINE_AA, false);
		y += textSize.height + lineSpacing;
	}

	//font->putText(image, str, cv::Point(this->offsetx, this->offsety), fontheight, CV_RGB(cR, cG, cB), cv::FILLED, cv::LINE_AA, true);
	return image;
}


//返回处理名称
std::string ImageSubTitle::ReturnName()
{
	return "字幕添加";
}



/*



下面是灰度处理


*/




ImageGray::ImageGray()
{

}




cv::Mat ImageGray::processImage(const cv::Mat& image)
{
	if (image.channels() == 1) {
		return image;
	}
	else {
		cv::Mat gray;
		cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		return gray;
	}

}


//返回处理名称
std::string ImageGray::ReturnName()
{
	return "灰度化";
}



/*


下面是二值化


*/



ImageBinaryzation::ImageBinaryzation():max(255), thresholdValue(177), thresholdType(0)
{

}


cv::Mat ImageBinaryzation::processImage(const cv::Mat& image)
{
	cv::Mat Binaryzation;
	cv::threshold(image, Binaryzation, this->thresholdValue, max, thresholdType);
	return Binaryzation;
}



void ImageBinaryzation::setThreshold(double thresholdValue, double max, int thresholdType)
{
	this->thresholdValue = thresholdValue;
	this->thresholdType = thresholdType;
}


//返回处理名称
std::string ImageBinaryzation::ReturnName()
{
	return "字幕添加";
}



/*


均值滤波

*/




ImageMeanFilter::ImageMeanFilter() :sizex(3), sizey(0), mdx(-1), mdy(-1), borderType(4)
{

}



cv::Mat ImageMeanFilter::processImage(const cv::Mat& image)
{
	cv::Mat mean;
	cv::blur(image, mean, cv::Size(sizex, sizey), cv::Point(mdx, mdy), borderType);
	return mean;
}



void ImageMeanFilter::SetParam(int sizex, int sizey, int mdx, int mdy, int borderType)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->mdx = mdx;
	this->mdy = mdy;
	this->borderType = borderType;
}


//返回处理名称
std::string ImageMeanFilter::ReturnName()
{
	return "均值滤波";
}



/*


高斯模糊算法

*/



ImageGaussianFilter::ImageGaussianFilter() :sizex(5), sizey(5), sigmaX(1.0), sigmaY(0), borderType(4)
{

}



cv::Mat ImageGaussianFilter::processImage(const cv::Mat& image)
{
	cv::Mat blurred;
	cv::GaussianBlur(image, blurred, cv::Size(sizex, sizey), sigmaX, sigmaY, borderType);
	return blurred;
}




/// <summary>
/// 设置配置参数
/// </summary>
/// <param name="sizex"></param>设置X轴尺寸
/// <param name="sizey"></param>设置Y轴尺寸
/// <param name="sigmaX"></param>
/// <param name="sigmaY"></param>
/// <param name="borderType"></param>边界模式
void ImageGaussianFilter::SetParam(int sizex, int sizey, double sigmaX, double sigmaY, int borderType)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->sigmaX = sigmaX;
	this->sigmaY = sigmaY;
	this->borderType = borderType;
}


//返回处理名称
std::string ImageGaussianFilter::ReturnName()
{
	return "高斯模糊";
}


/*

中值模糊算法

*/




ImageMedianFilter::ImageMedianFilter() :ksize(3)
{

}



cv::Mat ImageMedianFilter::processImage(const cv::Mat& image)
{
	cv::Mat filteredImage;
	// 中值滤波
	cv::medianBlur(image, filteredImage, ksize);
	return filteredImage;
}



void ImageMedianFilter::SetParam(int ksize)
{
	this->ksize = ksize;
}


//返回处理名称
std::string ImageMedianFilter::ReturnName()
{
	return "中值模糊";
}



/*

双边滤波算法

*/




ImageBilateralFilter::ImageBilateralFilter() :d(15), sigmaColor(75), sigmaSpace(75),borderType(4)
{

}



cv::Mat ImageBilateralFilter::processImage(const cv::Mat& image)
{
	cv::Mat result;
	cv::bilateralFilter(image, result, d, sigmaColor, sigmaSpace, borderType);
	return result;
}



void ImageBilateralFilter::SetParam(int d, double sigmaColor, double sigmaSpace, int borderType)
{
	this->d = d;
	this->sigmaColor = sigmaColor;
	this->sigmaSpace = sigmaSpace;
}



//返回处理名称
std::string ImageBilateralFilter::ReturnName()
{
	return "双边滤波";
}



/*


下面是亮度调整


*/


Bright::Bright():alpha(1.5)
{

}



cv::Mat Bright::processImage(const cv::Mat& image)
{
	cv::Mat brightenedImage;
	image.convertTo(brightenedImage, -1, alpha, 0);
	return brightenedImage;
}




void Bright::setThreshold(double alpha)
{
	this->alpha = alpha;
}


//返回处理名称
std::string Bright::ReturnName()
{
	return "亮度调整";
}



/*


下面是对比度调整


*/

Contrast::Contrast() :beta(50)
{

}


cv::Mat Contrast::processImage(const cv::Mat& image)
{
	cv::Mat contrastedImage;
	image.convertTo(contrastedImage, -1, 1, beta);
	return contrastedImage;
}




void Contrast::setThreshold(double beta)
{
	this->beta = beta;
}



//返回处理名称
std::string Contrast::ReturnName()
{
	return "对比度调整";
}



/*


下面是饱和度调整


*/

NTSC::NTSC() :alpha(1.5)
{

}


cv::Mat NTSC::processImage(const cv::Mat& image)
{
	cv::Mat saturatedImage;
	if (image.channels() == 3) {
		cv::cvtColor(image, saturatedImage, cv::COLOR_RGB2BGR); // 将图像转换为HSV颜色空间
		cv::cvtColor(saturatedImage, saturatedImage, cv::COLOR_RGB2HSV); // 将图像转换为HSV颜色空间
		std::vector<cv::Mat> channels;
		cv::split(saturatedImage, channels); // 拆分通道
		channels[1] *= alpha; // 调整饱和度通道
		cv::merge(channels, saturatedImage); // 合并通道
		cv::cvtColor(saturatedImage, saturatedImage, cv::COLOR_HSV2RGB); // 将图像转换回RGB颜色空间
		return saturatedImage;
	}
	else {
		return image;
	}

}




void NTSC::setThreshold(double alpha)
{
	this->alpha = alpha;
}



//返回处理名称
std::string NTSC::ReturnName()
{
	return "饱和度调整";
}



/*


下面是色温调整


*/

CCT::CCT() :temperature(5000)
{

}


cv::Mat CCT::processImage(const cv::Mat& image)
{
	double alpha = 1.5; // 饱和度增益因子
	cv::Mat saturatedImage;
	cv::cvtColor(image, saturatedImage, cv::COLOR_BGR2HSV); // 将图像转换为HSV颜色空间
	std::vector<cv::Mat> channels;
	cv::split(saturatedImage, channels); // 拆分通道
	channels[1] *= alpha; // 调整饱和度通道
	cv::merge(channels, saturatedImage); // 合并通道
	cv::cvtColor(saturatedImage, saturatedImage, cv::COLOR_HSV2BGR); // 将图像转换回BGR颜色空间

	return saturatedImage;
}




void CCT::setThreshold(double temperature)
{
	this->temperature = temperature;
}



//返回处理名称
std::string CCT::ReturnName()
{
	return "色温调整";
}




/*


下面是色阶调整


*/



Levels::Levels() :gamma(1.5)
{

}


cv::Mat Levels::processImage(const cv::Mat& image)
{
	cv::Mat adjustedImage;
	image.convertTo(adjustedImage, -1, 1, 0); // 将图像转换为可调整色阶的格式
	cv::pow(adjustedImage, gamma, adjustedImage); // 调整色阶

	return adjustedImage;
}




void Levels::setThreshold(double gamma)
{
	this->gamma = gamma;
}



//返回处理名称
std::string Levels::ReturnName()
{
	return "色阶调整";
}




/*


下面是直方图均衡化


*/



HistogramEqualization::HistogramEqualization()
{

}


cv::Mat HistogramEqualization::processImage(const cv::Mat& image)
{
	// 进行直方图均衡化
	cv::Mat equalized_image;
	equalizeHist(image, equalized_image);

	return equalized_image;
}



//返回处理名称
std::string HistogramEqualization::ReturnName()
{
	return "直方图均衡化";
}




/*


下面是膨胀


*/



Expand::Expand() :kernel(3)
{

}


cv::Mat Expand::processImage(const cv::Mat& image)
{
	
	cv::Size kernelSizeObj(kernel, kernel);
	// 定义结构元素
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, kernelSizeObj);

	// 进行膨胀操作
	cv::Mat dilated;
	cv::dilate(image, dilated, kernel);

	return dilated;
}




void Expand::setThreshold(int kernel)
{
	this->kernel = kernel;
}


//返回处理名称
std::string Expand::ReturnName()
{
	return "膨胀";
}





/*


下面是腐蚀


*/



Corrosion::Corrosion() :kernel(3)
{

}


cv::Mat Corrosion::processImage(const cv::Mat& image)
{
	
	cv::Size kernelSizeObj(kernel, kernel);


	// 定义结构元素
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, kernelSizeObj);

	// 进行腐蚀操作
	cv::Mat eroded;
	cv::erode(image, eroded, kernel);

	return eroded;
}




void Corrosion::setThreshold(int kernel)
{
	this->kernel = kernel;
}




//返回处理名称
std::string Corrosion::ReturnName()
{
	return "腐蚀";
}







/*


频谱转换

*/



SpectrumAnalysis::SpectrumAnalysis()
{

}


cv::Mat SpectrumAnalysis::processImage(const cv::Mat& image)
{

	if (image.channels() == 1) {

		// 将图像转换为浮点型
		cv::Mat imageFloat;
		image.convertTo(imageFloat, CV_32F);

		// 将图像尺寸调整为最接近的2的幂次方
		int m = cv::getOptimalDFTSize(imageFloat.rows);
		int n = cv::getOptimalDFTSize(imageFloat.cols);
		cv::Mat padded;
		cv::copyMakeBorder(imageFloat, padded, 0, m - imageFloat.rows, 0, n - imageFloat.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		//傅里叶变化
		cv::Mat complexImage;
		cv::dft(imageFloat, complexImage, cv::DFT_COMPLEX_OUTPUT);
		cv::Mat planes[] = { cv::Mat::zeros(image.size(), CV_32F), cv::Mat::zeros(image.size(), CV_32F) };
		cv::split(complexImage, planes);

		//计算频谱幅度
		cv::Mat magnitude;
		cv::magnitude(planes[0], planes[1], magnitude);


		//对数变化
		cv::Mat magnitudeLog;
		cv::log(magnitude + 1, magnitudeLog);

		//归一化
		cv::normalize(magnitudeLog, magnitudeLog, 0, 255, cv::NORM_MINMAX);

		//转换为灰度图像
		cv::convertScaleAbs(magnitudeLog, magnitudeLog);

		return magnitudeLog;
	}
	else {
		return image;
	}
}



void SpectrumAnalysis::setThreshold(double thresholdValue, int thresholdType)
{

}


//返回处理名称
std::string SpectrumAnalysis::ReturnName()
{
	return "频谱转换";
}


