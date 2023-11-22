#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>


#ifdef NEURALNETWORK_EXPORTS
#define NEURALNETWORK_API __declspec(dllexport)
#else
#define NEURALNETWORK_API __declspec(dllimport)
#endif


class NEURALNETWORK_API NeuralNetwork   
{
public:

    NeuralNetwork();

    ~NeuralNetwork();

    int LoadModel(const std::string& path);

    std::vector<float> ModelPrediction(const cv::Mat& image);

    cv::Mat ReadImage(const std::string& path);

    int SetImageRoi(int ROI1, int ROI2, int ROI3, int ROI4);


private:
    cv::dnn::dnn4_v20221220::Net Net;

    int xStrt;

    int yStart;

    int xEnd;

    int yEnd;

};



