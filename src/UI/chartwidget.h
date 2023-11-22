#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include "qcustomplot.h"

#if defined(zzxlib_ChartLib)
#  define ChartWidget_EXPORT Q_DECL_EXPORT
#else
#  define ChartWidget_EXPORT Q_DECL_IMPORT
#endif



namespace Ui {
class ChartWidget;
}

class ChartWidget_EXPORT ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);

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

    Ui::ChartWidget *ui;
};

#endif // CHARTWIDGET_H
