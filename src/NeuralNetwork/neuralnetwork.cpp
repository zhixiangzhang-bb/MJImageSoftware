#include "neuralnetwork.h"





 NeuralNetwork::NeuralNetwork():xStrt(900), yStart(400), xEnd(1600), yEnd(1200)
{

}



NeuralNetwork::~NeuralNetwork()
{

}



//加载模型
int NeuralNetwork::LoadModel(const std::string& path)
{
	Net=cv::dnn::readNetFromTensorflow(path);
	if (Net.empty())
	{
		return 0;
	}
	else {
		//Net.enableWinograd(false);
		return 1;
	}
}



//设置感兴趣的区域
int NeuralNetwork::SetImageRoi(int xStrt, int yStart, int xEnd, int yEnd)
{
	this->xStrt = xStrt;
	this->yStart = yStart;
	this->xEnd = xEnd;
	this->yEnd = yEnd;
	return 1;
}



//预测
std::vector<float> NeuralNetwork::ModelPrediction(const cv::Mat& image)
{		
	cv::Rect roi(xStrt, yStart, xEnd, yEnd);

	roi = roi & cv::Rect(0, 0, image.cols, image.rows);
	cv::Mat croppedImage = image(roi);

	// 将 4 通道图像转换为 3 通道图像
	if (croppedImage.channels() == 4) {
		cvtColor(croppedImage, croppedImage, cv::COLOR_BGRA2RGB);
	}

	//归一化处理
	cv::Mat blob = cv::dnn::blobFromImage(croppedImage, 1. / 255, cv::Size(roi.width, roi.height));

	Net.setInput(blob);
	std::vector<float> out;
	out=Net.forward();
	return out;
}



//离线读取
cv::Mat NeuralNetwork::ReadImage(const std::string& path)
{
	cv::Mat src;
	src = cv::imread(path);
	return src;
}