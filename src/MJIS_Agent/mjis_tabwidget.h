#pragma once


#include <QWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include "mjis_agent_macro.h"


/*****************************************************************
* 类名称：Tab页面类
* 功能描述：用各种项目类型填充，方便查询
* 作者：zzx
* 创建日期：2023.6.20
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




namespace Ui {
class Tabwidget;
}


class MJIS_Agent_API Tabwidget : public QWidget
{
    Q_OBJECT

public:
    //项目类型枚举，在建立时通过这个确认
    enum     VisualItemType {
        DefaultItem = -1,
        CameraItem,
        VideoItem,
        ImageItem,
    };

    explicit Tabwidget(QWidget *parent = nullptr);

    ~Tabwidget();

    //设置项目类型
    void SetItemStyle(VisualItemType Type);

    //获取项目类型
    VisualItemType GetItemStyle();

    //显示图片或者视频
    void ShowCameraQImage(const QImage& image);

    //设置名称文本
    void SetNameStr(const QString& name);

    //设置状态
    void SetState(const QString& state);

    //获取项目文本信息
    QString ReturnImfoString();


private:
    VisualItemType Type;

    std::shared_ptr<QGraphicsPixmapItem> pixmapItem;

    QGraphicsScene* scene;

    void closeEvent(QCloseEvent* event) override;

    Ui::Tabwidget *ui;


protected:
    void wheelEvent(QWheelEvent* event) override;



signals:
    void MyDockeWidgetClose();


private slots:
    void on_scaling_currentIndexChanged(int index);
};


