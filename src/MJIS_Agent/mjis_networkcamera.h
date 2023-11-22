#pragma once




#include <QDialog>
#include "mjis_agent_macro.h"
#include "mjis_camera.h"

namespace Ui {
class networkcamera;
}


class MJIS_Agent_API  networkcamera : public QDialog
{
    Q_OBJECT
public:
    explicit networkcamera(QWidget *parent = nullptr);
    ~networkcamera();

private:
    Ui::networkcamera *ui;

signals:
    void SelcetNetcamId(uint idex, mjis::ICamera::CameraType Type);


private slots:
    void on_update_clicked();

    void on_apply_clicked();

    void on_close_clicked();
};

