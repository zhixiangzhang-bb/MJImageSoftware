#ifndef RANDOMFORESTCONFIG_H
#define RANDOMFORESTCONFIG_H

#include <QWidget>

namespace Ui {
class randomforestconfig;
}

class RandomForestConfig : public QWidget
{
    Q_OBJECT

public:
    explicit RandomForestConfig(QWidget *parent = nullptr);

    ~RandomForestConfig();

    //获取设置的参数信息
    std::tuple<int, int, int, double, bool, int> ReturnCofig();


private:
    Ui::randomforestconfig *ui;
};

#endif // RANDOMFORESTCONFIG_H
