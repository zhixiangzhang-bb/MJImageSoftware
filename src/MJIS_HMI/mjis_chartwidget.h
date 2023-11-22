#pragma once


#include <QWidget>
#include "qcustomplot.h"
#include "mjis_hmi_global.h"




namespace Ui {
class ChartWidget;
}

namespace mjis {

    namespace hmi {

        class  MJIS_HMI_API ChartWidget : public QWidget
        {
            //Q_OBJECT

        public:
            explicit ChartWidget(QWidget* parent = nullptr);

            ~ChartWidget();

            //设置XY轴名称
            void SetXYName(QString X, QString Y);

            //绘制直方图
            void Histogram(QVector<double> xData, QVector<double> yData);

            //添加一条曲线
            void AddCurve(const QString& name, const QPen& color);

            //绘制拟合曲线
            void FittedCurve();

            //更新图表
            void UpdataChart(const QVector<double>& xData, const QVector<double>& yData, int idex);

            //更新图像适应界面
            void RescaleAxes();


        private:
            //曲线列表
            QVector<std::shared_ptr<QCPGraph>> GraphList;

            Ui::ChartWidget* ui;
        };
    }
}

