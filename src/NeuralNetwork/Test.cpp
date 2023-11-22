#include "cnn.h"





int main()
{
	
	cv::Mat src = cv::imread("D:/t/Image_0914.jpg");

	auto mode = CreateModel();
	LoadModel(mode,"D:/Work/CNN_Model/frozen_graph.pb");
	auto start = std::chrono::high_resolution_clock::now();


	unsigned char* data = reinterpret_cast<unsigned char*>(src.ptr());

	std::cout << ReasoningModel(mode, data,10,800,700,3) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	std::cout << "Time taken by function: " << duration << " microseconds" << std::endl;

}



