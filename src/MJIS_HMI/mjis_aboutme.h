
#pragma once

#include <QDialog>
#include "mjis_hmi_global.h"



namespace Ui {
class AboutMe;
}


namespace mjis {

    namespace hmi {

        class MJIS_HMI_API  AboutMe : public QDialog
        {
            //Q_OBJECT

        public:
            explicit AboutMe(QWidget* parent = nullptr);
            ~AboutMe();

        private:
            Ui::AboutMe* ui;
        };

    }
}

