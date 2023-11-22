



#include "mjis_chartwidget.h"
#include "ui_mjis_chartwidget.h"

namespace mjis {

    namespace hmi {

        ChartWidget::ChartWidget(QWidget* parent) :
            QWidget(parent),
            ui(new Ui::ChartWidget)
        {
            ui->setupUi(this);
        }




        ChartWidget::~ChartWidget()
        {
            delete ui;
        }


        void ChartWidget::SetXYName(QString X, QString Y)
        {
            ui->widget->xAxis->setLabel(X);
            ui->widget->yAxis->setLabel(Y);
        }



        void ChartWidget::Histogram(QVector<double> xData, QVector<double> yData)
        {
            //直方图
            QCPBars* histogram = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
            histogram->setData(xData, yData);
            histogram->setPen(Qt::NoPen);
            histogram->setBrush(QColor(50, 50, 200, 70));

            //曲线图
            QCPGraph* graph = ui->widget->addGraph();
            graph->setData(xData, yData);
            graph->setPen(QPen(Qt::blue));
            graph->setBrush(QBrush(QColor(0, 0, 255, 20)));

            // 调整坐标轴范围以适应屏幕大小
            ui->widget->rescaleAxes();
            // 重新绘制图形
            ui->widget->replot();
        }


        //更新图像适应界面
        void ChartWidget::RescaleAxes()
        {
            // 调整坐标轴范围以适应屏幕大小
            ui->widget->rescaleAxes();
            // 重新绘制图形
            ui->widget->replot();
        }



        //添加一条曲线
        void ChartWidget::AddCurve(const QString& name, const QPen& color)
        {
            // 创建训练误差曲线
            std::shared_ptr<QCPGraph> gp(ui->widget->addGraph());
            GraphList.append(gp);
            gp->setName(name);
            gp->setPen(color);
        }


        //绘制拟合曲线
        void ChartWidget::FittedCurve()
        {
            // 设置图形及坐标轴属性
            ui->widget->plotLayout()->insertRow(0);
            ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Learning Curve", QFont("sans", 12, QFont::Bold)));
            ui->widget->xAxis->setLabel("Iterations");
            ui->widget->yAxis->setLabel("Error");
            ui->widget->legend->setVisible(true);
            //ui->widget->legend->setPositionStyle(QCPLegend::psTopRight);

            AddCurve("训练误差", QPen(Qt::blue));

            AddCurve("验证误差", QPen(Qt::red));

        }


        //更新图表
        void ChartWidget::UpdataChart(const QVector<double>& xData, const QVector<double>& yData, int idex)
        {
            //更新曲线
            GraphList[idex]->setData(xData, yData);

            // 调整坐标轴范围以适应屏幕大小
            ui->widget->rescaleAxes();

            // 重新绘制图形
            ui->widget->replot();
        }

    }
}