#include "cnn.h"


//创建模型
extern "C"  uint32_t * CreateModel()
{
	auto out = new NeuralNetwork();
	return reinterpret_cast<uint32_t*>(out);
}




//加载模型
extern "C"   int LoadModel(uint32_t* model, const char* path)
{
	auto net = reinterpret_cast<NeuralNetwork*>(model);
	return net->LoadModel(path);
}




//设置感兴趣的区域
extern "C"   int SetImageROI(uint32_t * model, int Roi1, int Roi2, int Roi3, int Roi4)
{
	auto net = reinterpret_cast<NeuralNetwork*>(model);
	net->SetImageRoi(Roi1, Roi2, Roi3, Roi4);
	return 1;
}
	


//读取图片并预测
extern "C"  float ReadImage(uint32_t* model,const char* path)
{
	cv::Mat src;

	std::string str(path);

	src = cv::imread(str);

	auto net = reinterpret_cast<NeuralNetwork*>(model);

	auto a=net->ModelPrediction(src);

	return a[0];
}




//测试用，截取ROI
extern "C"   unsigned char* ImageROI(uint32_t * model, unsigned char* LVImagePointer, int lineWidth, int height, int width)
{
	cv::Mat image(height, lineWidth, CV_8UC4, LVImagePointer);

	// 裁剪图像
	cv::Rect roi(0, 0, width, height);
	cv::Mat croppedImage = image(roi);


	return  reinterpret_cast<unsigned char*>(image.ptr());

}




	
//预测模型
extern "C"  float ReasoningModel(uint32_t * model, unsigned char* LVImagePointer, int lineWidth, int height, int width,int channels)
{
	cv::Mat image;
	if (channels == 1) {
		image=cv::Mat(height, lineWidth, CV_8UC1, LVImagePointer);
	}
	else if(channels==3){
		image = cv::Mat(height, lineWidth, CV_8UC3, LVImagePointer);
	}
	else if (channels == 4) {
		image = cv::Mat(height, lineWidth, CV_8UC4, LVImagePointer);
	}


	cv::Rect roi(0, 0, width, height);
	roi = roi & cv::Rect(0, 0, image.cols, image.rows);
	cv::Mat croppedImage = image(roi);

	auto net = reinterpret_cast<NeuralNetwork*>(model);
	auto a = net->ModelPrediction(croppedImage);
	return a[0];
}



//删除模型
extern "C"   int DeleteModel(uint32_t * model)
{
	auto net = reinterpret_cast<NeuralNetwork*>(model);
	delete net;
	return 0;
}

