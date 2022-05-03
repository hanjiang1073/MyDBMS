#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <QWidget>
#include <QMessageBox>
#include "registframe.h"
namespace Ui {
class LoginFrame;
}

class LoginFrame : public QWidget
{
    Q_OBJECT

public:
    explicit LoginFrame(QWidget *parent = nullptr);
    ~LoginFrame();
    void initConnection();//创建连接
    void readUsers();
    void writeUsers();
signals:
    void login(QString);
    void closeframe();
private:
    Ui::LoginFrame *ui;
    QString rname;
    QString rpw;
    RegistFrame *rf;
public slots:
    void btn_reset_clicked();//重置按钮
    void btn_login_clicked();//登入按钮
    void btn_regist_clicked();//注册按钮
    void reg_login(QString);//注册的登入（用于传递信号）
};

#endif // LOGINFRAME_H
