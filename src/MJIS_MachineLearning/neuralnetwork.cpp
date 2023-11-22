#include "neuralnetwork.h"
#include "machinelearning.h"



NeuralNetwork::NeuralNetwork():width(800), height(600)
{

}



NeuralNetwork::~NeuralNetwork()
{

}



//加载模型
void NeuralNetwork::LoadModel(const std::string& path)
{
	Net = cv::dnn::readNetFromTensorflow(path);
}




//预测
std::vector<float> NeuralNetwork::ModelPrediction(const cv::Mat& image)
{
	//归一化处理
	cv::Mat blob = cv::dnn::blobFromImage(image, 1. / 255, cv::Size(width, height));

	Net.setInput(blob);
	std::vector<float> out;
	Net.enableWinograd(false);
	out = Net.forward();

	return out;
}


