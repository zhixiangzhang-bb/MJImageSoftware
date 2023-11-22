#include "configinterface.h"
#include "ui_configinterface.h"
#include <QFileDialog>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

namespace zzxml {
    ConfigInterface::ConfigInterface(QWidget* parent) :
        QWidget(parent), type(No),
        ui(new Ui::ConfigInterface)
    {
        ui->setupUi(this);
    }



    ConfigInterface::~ConfigInterface()
    {
        delete ui;
    }


    //读取OK文件预加载数据
    void ConfigInterface::ReadOkPreData()
    {
        // 创建一个文件选择对话框
        QFileDialog dialog;

        // 设置对话框选项
        dialog.setFileMode(QFileDialog::Directory);  // 可选择任意文件
        dialog.setViewMode(QFileDialog::Detail);   // 显示详细信息

        // 弹出文件选择对话框
        if (dialog.exec())
        {
            // 获取选择的文件路径
            okpath = dialog.selectedFiles().at(0).toLocal8Bit().toStdString();

            auto future = QtConcurrent::run([&]() {
                this->ReadPreData(okpath);

                });

            // 异步执行computeSum函数，并返回一个std::future对象
            auto futureResult = std::async(std::launch::async | std::launch::deferred ,&ConfigInterface::ReadPreData, this, std::ref(okpath));
        }
    }



    //读取文件夹
    std::vector<cv::Mat>  ConfigInterface::ReadPreData(std::string& path)
    {
        // 加载训练数据和标签
        std::vector<cv::Mat> data;

        // 加载文件夹1中的图像数据
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (file.is_regular_file()) {
                cv::Mat image = cv::imread(file.path().string(), cv::IMREAD_GRAYSCALE);
                if (image.empty()) {
                    std::cerr << "Failed to load image: " << file.path().string() << std::endl;
                    continue;
                }
                data.push_back(image);
            }
        }
        return data;
    }


    //开始训练
    void ConfigInterface::StartTrain()
    {

    }


}

