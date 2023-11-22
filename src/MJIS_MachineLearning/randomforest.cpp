
#include "randomforest.h"
#include <filesystem>

namespace zzxml {


    RandomForest::RandomForest():config(new RandomForestConfig),
        depth(0), mincount(0), max_iterations(-1), epsilon(0.01), importance(false), randomcount(0)
    {

    }



    RandomForest::~RandomForest()
    {

    }

    //返回配置页面
    RandomForestConfig* RandomForest::ReturnConfig()
    {
        return config.get();
    }


    //预加载数据
    void RandomForest::PreLoadData()
    {


    }



    //模型训练
    void RandomForest::ModelTrain()
    {

        std::string folder1 = okpath;
        std::string folder2 = ngpath;

        // 加载训练数据和标签
        std::vector<cv::Mat> trainData;
        std::vector<int> labels;

        // 加载文件夹1中的图像数据
        for (const auto& file : std::filesystem::directory_iterator(folder1)) {
            if (file.is_regular_file()) {
                cv::Mat image = cv::imread(file.path().string(), cv::IMREAD_GRAYSCALE);
                if (image.empty()) {
                    std::cerr << "Failed to load image: " << file.path().string() << std::endl;
                    continue;
                }

                trainData.push_back(image);
                labels.push_back(0);  // 类别1的标签为0
            }
        }


        // 加载文件夹2中的图像数据
        for (const auto& file : std::filesystem::directory_iterator(folder2)) {
            if (file.is_regular_file()) {
                cv::Mat image = cv::imread(file.path().string(), cv::IMREAD_GRAYSCALE);
                if (image.empty()) {
                    std::cerr << "Failed to load image: " << file.path().string() << std::endl;
                    continue;
                }

                trainData.push_back(image);
                labels.push_back(1);  // 类别2的标签为1
            }
        }


        // 创建训练数据矩阵
        int numSamples = trainData.size();
        int numFeatures = trainData[0].rows * trainData[0].cols * trainData[0].channels();
        cv::Mat trainDataMat(numSamples, numFeatures, CV_32FC1);
        for (int i = 0; i < numSamples; ++i) {
            cv::Mat image = trainData[i].reshape(1, 1);  // 将图像展平为一维行向量
            image.convertTo(image, CV_32FC1);  // 转换为单精度浮点型
            cv::Mat row = trainDataMat.row(i);
            image.copyTo(row);
        }

        // 创建标签矩阵
        cv::Mat labelsMat(labels.size(), 1, CV_32SC1, labels.data());

        // 创建并训练随机森林模型
        cv::Ptr<cv::ml::RTrees> randomForest = cv::ml::RTrees::create();

        randomForest->setMaxDepth(10); // 设置随机森林最大深度
        randomForest->setMinSampleCount(2); // 设置每个叶子节点的最小样本数
        randomForest->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 100, 0.01)); // 设置迭代终止条件

        randomForest->train(trainDataMat, cv::ml::ROW_SAMPLE, labelsMat);

        // 保存模型
        randomForest->save("E:/ZImageSoft/CavitationAPP/Test/model.xml");
    }



    //模型测试
    void RandomForest::TestModel()
    {
        // 创建随机森林模型
        cv::Ptr<cv::ml::RTrees> randomForest = cv::ml::RTrees::create();

        // 加载模型
        randomForest = cv::Algorithm::load<cv::ml::RTrees>("E:/ZImageSoft/CavitationAPP/Test/model.xml");

        //QString str1 = "F:/桌面/G01523 东电抽蓄模型试验台/设计文件/空化照片/N/Image_0566.jpg";

        //std::string folder1 = str1.toLocal8Bit().data();

        std::string folder1 = "F:/桌面/G01523 东电抽蓄模型试验台/设计文件/空化照片/N/Image_0566.jpg";

        // 使用模型进行预测
        cv::Mat image = cv::imread(folder1, cv::IMREAD_GRAYSCALE);
        cv::Mat testSample = image.reshape(1, 1);  // 将图像展平为一维向量
        testSample.convertTo(testSample, CV_32FC1);  // 转换为单精度浮点型

        cv::Mat prediction;
        randomForest->predict(testSample, prediction);

        // 输出预测结果
        std::cout << "Prediction: " << prediction << std::endl;
    }


    //设置分类1路径
    void RandomForest::SetOkPath(std::string& path)
    {
        okpath = path;
    }



    //设置分类2路径
    void RandomForest::SetNgPath(std::string& path)
    {
        ngpath = path;
    }



    //设置分类1路径
    void RandomForest::SetModelPath(std::string& path)
    {
        modelpath = path;
    }


    //绘制拟合曲线
    mjis::hmi::ChartWidget* RandomForest::ReturnFitChart()
    {
        chart = std::make_shared<mjis::hmi::ChartWidget>();
        chart->FittedCurve();
        return chart.get();
    }
}

