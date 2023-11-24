#pragma once


#include <QDialog>
#include "mjlib_vision_api.h"
#include "mjis_hmi_global.h"




/*****************************************************************
* 类名称：二值化配置界面
* 功能描述：用于配置二值化信息，同时返回二值化处理指针
* 作者：zzx
* 创建日期：2023.8.16
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/


namespace Ui {
    class BinaryImageui;
    class mean;
    class Gaussian;
    class Median;
    class Bilateral;
    class Bilateral;
}

namespace mjis {

    namespace hmi {


        class BinaryImageui : public QDialog
        {
            Q_OBJECT

        public:
            explicit BinaryImageui(QWidget* parent = nullptr);

            ~BinaryImageui();

            //返回二值化指针
            mjlib::ImageBinaryzation* ReturnBinary();
        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();

        private:
            mjlib::ImageBinaryzation* ib;

            Ui::BinaryImageui* ui;
        };



        /*****************************************************************
        * 类名称：均值滤波参数配置界面
        * 功能描述：配置参数，并且可以返回处理指针
        * 作者：zzx
        * 创建日期：2023.8.16
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/





        class Mean : public QDialog
        {
            Q_OBJECT

        public:
            explicit Mean(QWidget* parent = nullptr);
            ~Mean();

            //返回滤波指针
            mjlib::ImageMeanFilter* ReturnMean();

        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();


        private:
            mjlib::ImageMeanFilter* imf;

            Ui::mean* ui;
        };




        /*****************************************************************
        * 类名称：高斯滤波参数配置界面
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.8.16
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/




        class Gaussian : public QDialog
        {
            Q_OBJECT

        public:
            explicit Gaussian(QWidget* parent = nullptr);

            ~Gaussian();

            //返回高斯模糊
            mjlib::ImageGaussianFilter* ReturnGaussian();

        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();

        private:
            mjlib::ImageGaussianFilter* igf;

            Ui::Gaussian* ui;
        };




        /*****************************************************************
        * 类名称：中值滤波参数
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.8.16
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/




        class Median : public QDialog
        {
            Q_OBJECT

        public:
            explicit Median(QWidget* parent = nullptr);

            ~Median();

            //返回高斯模糊
            mjlib::ImageMedianFilter* ReturnMedian();

        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();

        private:
            mjlib::ImageMedianFilter* imf;

            Ui::Median* ui;
        };



        /*****************************************************************
        * 类名称：双边滤波参数
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.8.16
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/





        class Bilateral : public QDialog
        {
            Q_OBJECT

        public:
            explicit Bilateral(QWidget* parent = nullptr);

            ~Bilateral();

            //返回双边滤波
            mjlib::ImageBilateralFilter* ReturnBilateral();

        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();

        private:
            mjlib::ImageBilateralFilter* ibf;

            Ui::Bilateral* ui;
        };


    }
}