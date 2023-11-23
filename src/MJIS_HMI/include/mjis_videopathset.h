#ifndef VIDEOPATHSET_H
#define VIDEOPATHSET_H

#include <QDialog>
#include <QSettings>
#include "mjis_hmi_global.h"


namespace Ui {
class VideoPathSet;
}

namespace mjis {

    namespace hmi {

        class MJIS_HMI_API VideoPathSet : public QDialog
        {
            Q_OBJECT

        public:
            explicit VideoPathSet(QWidget* parent = nullptr);
            ~VideoPathSet();

        private slots:

            void on_pushButton_3_clicked();

            void on_pushButton_2_clicked();

            void on_toolButton_clicked();

            void on_toolButton_2_clicked();

        private:
            Ui::VideoPathSet* ui;
        };

    }
}
#endif // VIDEOPATHSET_H
