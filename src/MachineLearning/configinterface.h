#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H

#include <QWidget>
#include "machinelearning.h"
#include "randomforest.h"

/*****************************************************************
* 类名称：机器训练配置界面
* 功能描述：训练界面
* 作者：zzx
* 创建日期：2023.8.16
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



namespace Ui {
    class ConfigInterface;
}

namespace zzxml {
    class MachineLearning_API  ConfigInterface : public QWidget
    {
        Q_OBJECT

        enum MlType {
            No = -1,
            RandomForest,
            SVM
        };


    public:

        explicit ConfigInterface(QWidget* parent = nullptr);

        ~ConfigInterface();

        //开始训练
        void StartTrain();

        //读取OK文件预加载数据
        void ReadOkPreData();

        //读取文件夹
        std::vector<cv::Mat> ReadPreData(std::string& path);


    private slots:
        

    private:
        //训练类型
        MlType type;

        //分类2加载路径
        std::string ngpath;

        //分类1加载路径
        std::string okpath;

        Ui::ConfigInterface* ui;
    };
}


#endif // CONFIGINTERFACE_H
