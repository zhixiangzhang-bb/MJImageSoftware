#ifndef VIDEOPATHSET_H
#define VIDEOPATHSET_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class VideoPathSet;
}

class VideoPathSet : public QDialog
{
    Q_OBJECT

public:
    explicit VideoPathSet(QWidget *parent = nullptr);
    ~VideoPathSet();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::VideoPathSet *ui;
};

#endif // VIDEOPATHSET_H
