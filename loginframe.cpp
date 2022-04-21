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
    //由于用户表还没写这里就先全空就能上
    if(name==""&&pw==""){
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("登入成功！"));
        emit(login());
        this->close();
    }else{
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("用户名或密码错误！"));
    }

}

//重置按钮
void LoginFrame::btn_reset_clicked(){
    ui->edit_name->clear();
    ui->edit_pw->clear();
}
//注册的登入传递信号
void LoginFrame::reg_login(){
    emit(login());
    this->close();
}
//注册按钮
void LoginFrame::btn_regist_clicked(){
    rf=new RegistFrame();
    rf->show();
    connect(rf,SIGNAL(confirm()),this,SLOT(reg_login()));
}
