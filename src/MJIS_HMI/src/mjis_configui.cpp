#include "mjis_configui.h"
#include "ui_binaryimageui.h"
#include "ui_mean.h"
#include "ui_gaussian.h"
#include "ui_median.h"
#include "ui_Bilateral.h"


namespace mjis {

    namespace hmi {


        BinaryImageui::BinaryImageui(QWidget* parent) :
            QDialog(parent), ib(nullptr),
            ui(new Ui::BinaryImageui)
        {
            ui->setupUi(this);
            this->setWindowTitle("二值化配置");
        }


        BinaryImageui::~BinaryImageui()
        {
            delete ui;
        }


        //确认选择
        void BinaryImageui::on_buttonBox_accepted()
        {
            ib = new mjlib::ImageBinaryzation;
            ib->setThreshold(ui->threshold->value(), ui->max->value(), ui->select->currentIndex());
            this->close();
        }


        //取消选择
        void BinaryImageui::on_buttonBox_rejected()
        {
            this->close();
        }


        //返回二值化指针
        mjlib::ImageBinaryzation* BinaryImageui::ReturnBinary()
        {
            return ib;
        }





        /*




        */





        Mean::Mean(QWidget* parent) :
            QDialog(parent), imf(nullptr),
            ui(new Ui::mean)
        {
            ui->setupUi(this);
            this->setWindowTitle("均值滤波配置");
        }


        Mean::~Mean()
        {
            delete ui;
        }


        void Mean::on_buttonBox_accepted()
        {
            imf = new mjlib::ImageMeanFilter;
            imf->SetParam(ui->hx->value(), ui->hy->value(), ui->mx->value(), ui->my->value(), ui->select->currentIndex());
            this->close();
        }


        void Mean::on_buttonBox_rejected()
        {
            this->close();
        }


        //返回滤波指针
        mjlib::ImageMeanFilter* Mean::ReturnMean()
        {
            return imf;
        }




        /*

        高斯滤波配置实现



        */





        Gaussian::Gaussian(QWidget* parent) :
            QDialog(parent), igf(nullptr),
            ui(new Ui::Gaussian)
        {
            ui->setupUi(this);
        }

        Gaussian::~Gaussian()
        {
            delete ui;
        }


        void Gaussian::on_buttonBox_accepted()
        {
            igf = new mjlib::ImageGaussianFilter;
            igf->SetParam(ui->gshx->value(), ui->gshy->value(), ui->stdx->value(), ui->stdy->value(), ui->select->currentIndex());
            this->close();
        }


        void Gaussian::on_buttonBox_rejected()
        {
            this->close();
        }


        //返回高斯模糊
        mjlib::ImageGaussianFilter* Gaussian::ReturnGaussian()
        {
            return igf;
        }




        /// <summary>
        /// 中值滤波逻辑
        /// </summary>
        /// <param name="parent"></param>




        Median::Median(QWidget* parent) :
            QDialog(parent), imf(nullptr),
            ui(new Ui::Median)
        {
            ui->setupUi(this);
        }

        Median::~Median()
        {
            delete ui;
        }


        void Median::on_buttonBox_accepted()
        {
            if (imf == nullptr) {
                imf = new mjlib::ImageMedianFilter;
            }
            imf->SetParam(ui->size->value());
            this->close();
        }


        void Median::on_buttonBox_rejected()
        {
            this->close();
        }


        //返回高斯模糊
        mjlib::ImageMedianFilter* Median::ReturnMedian()
        {
            return imf;
        }


        /// <summary>
        /// 双边滤波逻辑
        /// </summary>
        /// <param name="parent"></param>




        Bilateral::Bilateral(QWidget* parent) :
            QDialog(parent), ibf(nullptr),
            ui(new Ui::Bilateral)
        {
            ui->setupUi(this);
        }

        Bilateral::~Bilateral()
        {
            delete ui;
        }


        void Bilateral::on_buttonBox_accepted()
        {
            if (ibf == nullptr) {
                ibf = new mjlib::ImageBilateralFilter;
            }
            ibf->SetParam(ui->dd->value(), ui->sigmaColor->value(), ui->sigmaSpace->value(), ui->type->currentIndex());
            this->close();
        }


        void Bilateral::on_buttonBox_rejected()
        {
            this->close();
        }


        //返回双边模糊
        mjlib::ImageBilateralFilter* Bilateral::ReturnBilateral()
        {
            return ibf;
        }

    }
}