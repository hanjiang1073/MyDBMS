#ifndef SQLINPUT_H
#define SQLINPUT_H

#include <QWidget>

namespace Ui {
class SqlInput;
}

class SqlInput : public QWidget
{
    Q_OBJECT

public:
    explicit SqlInput(QWidget *parent = nullptr);
    ~SqlInput();

private:
    Ui::SqlInput *ui;
};

#endif // SQLINPUT_H
