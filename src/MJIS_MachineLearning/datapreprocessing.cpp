#include "datapreprocessing.h"
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace zzxml {
    DataPreprocessing::DataPreprocessing()
    {

    }


    DataPreprocessing::~DataPreprocessing()
    {

    }


    //加载预览数据
    std::vector<cv::Mat> DataPreprocessing::LoadPreData(std::string path)
    {
        std::vector<cv::Mat> predata;
        // 加载文件夹1中的图像数据
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (file.is_regular_file()) {
                cv::Mat image = cv::imread(file.path().string(), cv::IMREAD_GRAYSCALE);
                if (image.empty()) {
                    std::cerr << "Failed to load image: " << file.path().string() << std::endl;
                    continue;
                }

                predata.push_back(image);
            }
        }
        return predata;
    }


}