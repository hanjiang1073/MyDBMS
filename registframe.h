#ifndef REGISTFRAME_H
#define REGISTFRAME_H

#include <QWidget>
#include <QMessageBox>
#include"tfile.h"
#include"dfile.h"
namespace Ui {
class RegistFrame;
}

class RegistFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RegistFrame(QWidget *parent = nullptr);
    ~RegistFrame();
signals:
    void confirm(QString);
private:
    Ui::RegistFrame *ui;
public slots:
    void btn_confirm_clicked();
    void on_checkBox_dba();
};

#endif // REGISTFRAME_H
