#pragma once




#include <QDialog>
#include "mjis_hmi_global.h"
#include "mjis_mvcamera.h"

namespace Ui {
class networkcamera;
}



namespace mjis {

    namespace hmi {

        class MJIS_HMI_API  networkcamera : public QDialog
        {
            Q_OBJECT
        public:
            explicit networkcamera(QWidget* parent = nullptr);
            ~networkcamera();

        private:
            Ui::networkcamera* ui;

        signals:
            void SelcetNetcamId(uint idex, mjis::camera::ICamera::CameraType Type);


        private slots:
            void on_update_clicked();

            void on_apply_clicked();

            void on_close_clicked();
        };

    }
}