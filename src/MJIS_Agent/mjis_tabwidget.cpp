﻿#include "mjis_tabwidget.h"
#include "ui_mjis_tabwidget.h"

Tabwidget::Tabwidget(QWidget* parent) :
    QWidget(parent),
    Type(DefaultItem),
    pixmapItem(new QGraphicsPixmapItem),
    scene(new QGraphicsScene),
    ui(new Ui::Tabwidget)
{
    ui->setupUi(this);   
    ui->ImageShow->setScene(scene);
    scene->addItem(pixmapItem.get());
}


Tabwidget::~Tabwidget()
{
    delete ui;
}


void Tabwidget::SetItemStyle(VisualItemType Type)
{
    this->Type = Type;
}


Tabwidget::VisualItemType Tabwidget::GetItemStyle()
{
    return this->Type;
}



void Tabwidget::ShowCameraQImage(const QImage& image)//返回转化的Qimage
{
    QPixmap pmp = QPixmap::fromImage(image);
    pixmapItem->setPixmap(pmp);
    scene->update();
}


//设置名称文本
void Tabwidget::SetNameStr(const QString& name)
{
    ui->statestr->setText(name);
}

            
//设置状态  
void Tabwidget::SetState(const QString& state)
{
    ui->name->setText(state);
}


void Tabwidget::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        // 获取当前的缩放因子
        qreal scaleFactor = ui->ImageShow->transform().m11();

        // 根据滑轮滚动的方向，进行放大或缩小
        if (event->angleDelta().y() > 0)
        {
            scaleFactor *= 1.2;
        }
        else
        {
            scaleFactor /= 1.2;
        }

        // 设置新的缩放因子
        ui->ImageShow->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));

        QString str = QString::number(scaleFactor * 100, 'f', 0) + "%";
        ui->scaling->setEditText(str);

        // 阻止事件继续传递给父类处理
        event->accept();
    }
    else
    {
        // 如果没有按下Ctrl键，则将事件传递给父类处理
        //QGraphicsView::wheelEvent(event);
    }
}



void Tabwidget::closeEvent(QCloseEvent* event)
{
    int ret = QMessageBox::question(this, "提示", "是否关闭本窗口", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        emit MyDockeWidgetClose();
    }
}



//比例选择变化
void Tabwidget::on_scaling_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->ImageShow->setTransform(QTransform::fromScale(0.25, 0.25));
        break;
    case 1:
        ui->ImageShow->setTransform(QTransform::fromScale(0.5, 0.5));
        break;
    case 2:
        ui->ImageShow->setTransform(QTransform::fromScale(1, 1));
        break;
    case 3:
        ui->ImageShow->setTransform(QTransform::fromScale(1.5, 1.5));
        break;
    case 4:
        ui->ImageShow->setTransform(QTransform::fromScale(2.0, 2.0));
        break;
    default:
        break;
    }
}


//获取项目文本信息
QString Tabwidget::ReturnImfoString()
{
    return nullptr;
}

