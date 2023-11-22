#pragma once


#include <QDialog>
#include "mjis_agent_macro.h"
#include "mjis_localcamera.h"

/*****************************************************************
* 类名称：本地相机UI
* 功能描述：搜索和加入相机
* 作者：zzx
* 创建日期：2023.7.10
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



namespace Ui {
class LocalCameraUI;
}

class  MJIS_Agent_API LocalCameraUI : public QDialog
{
    Q_OBJECT

public:
    explicit LocalCameraUI(QWidget *parent = nullptr);
    ~LocalCameraUI();

    

private slots:
    //搜索按钮点击
    void on_select_clicked();

    //应用选择按钮
    void on_appy_clicked();

    //关闭按钮
    void on_close_clicked();

    //数值变化
    void on_number_valueChanged(int arg1);


signals:
    void SelcetNetcamId(uint idex, mjis::ICamera::CameraType Type);

private:
    Ui::LocalCameraUI *ui;
};


