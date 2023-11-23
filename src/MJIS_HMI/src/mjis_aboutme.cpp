#include "mjis_aboutme.h"
#include "ui_mjis_aboutme.h"
#include <QFile>


namespace mjis {

    namespace hmi {

        AboutMe::AboutMe(QWidget* parent) :
            QDialog(parent),
            ui(new Ui::AboutMe)
        {
            ui->setupUi(this);

            setWindowTitle("关于作者");

        }



        AboutMe::~AboutMe()
        {
            delete ui;
        }

    }
}