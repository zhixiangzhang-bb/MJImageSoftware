#pragma once
#include <string>
#include <opencv2/opencv.hpp>

namespace zzxml {

	class DataPreprocessing
	{
	public:

		DataPreprocessing();

		~DataPreprocessing();

		//加载预览数据
		static std::vector<cv::Mat> LoadPreData(std::string path);


	private:

	};




}
		
