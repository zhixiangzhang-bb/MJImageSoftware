#pragma once
#include "datapreprocessing.h"





/*****************************************************************
* 类名称：数据界面类
* 功能描述：显示功能
* 作者：zzx
* 创建日期：2023.7.31
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



//卷积神经网络
class NeuralNetwork
{
public:

    NeuralNetwork();

    ~NeuralNetwork();

    //加载模型
    void LoadModel(const std::string& path);

    //预测
    std::vector<float> ModelPrediction(const cv::Mat& image);


private:
    //模型实例
    cv::dnn::dnn4_v20221220::Net Net;

    //宽度
    int width;

    //高度
    int height;


};
