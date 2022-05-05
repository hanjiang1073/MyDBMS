#include "loginframe.h"
#include "ui_loginframe.h"

LoginFrame::LoginFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginFrame)
{
    ui->setupUi(this);
    initConnection();
}

LoginFrame::~LoginFrame()
{
    delete ui;
}

// 初始化各控件
void LoginFrame::initConnection(){
    connect(ui->btn_login,SIGNAL(clicked()),this,SLOT(btn_login_clicked()));
    connect(ui->btn_reset,SIGNAL(clicked()),this,SLOT(btn_reset_clicked()));
    connect(ui->btn_regist,SIGNAL(clicked()),this,SLOT(btn_regist_clicked()));
    ui->edit_pw->setEchoMode(QLineEdit::Password);
}

//登入按钮
void LoginFrame::btn_login_clicked(){
    QString name=ui->edit_name->text();
    QString pw=ui->edit_pw->text();
    //TODO这里查询用户表的信息如果对的上那么就登入
    int result = DFile().userexist(name,pw);

    //由于用户表还没写这里是测试
    if(result==1){
<<<<<<< HEAD
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("登入成功！"));
        emit(login(name));//传递登入信号并传参
        this->close();
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("用户名或密码错误！"));
=======
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("登入成功！"));
        emit(login(name));//传递登入信号并传参
        this->close();
    }else{
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("用户名或密码错误！"));
>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a
    }

}

//重置按钮
void LoginFrame::btn_reset_clicked(){
    ui->edit_name->clear();
    ui->edit_pw->clear();
}
//注册的登入传递信号
void LoginFrame::reg_login(QString name){
    emit(login(name));
    this->close();
}
//注册按钮
void LoginFrame::btn_regist_clicked(){
    rf=new RegistFrame();
    rf->show();
    connect(rf,SIGNAL(confirm(QString)),this,SLOT(reg_login(QString)));
}
