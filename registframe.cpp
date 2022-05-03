#include "registframe.h"
#include "ui_registframe.h"

RegistFrame::RegistFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistFrame)
{
    ui->setupUi(this);
    connect(ui->btn_confirm,SIGNAL(clicked()),this,SLOT(btn_confirm_clicked()));
}

RegistFrame::~RegistFrame()
{
    delete ui;
}

//注册确认
void RegistFrame::btn_confirm_clicked(){
    QString name=ui->edit_name->text();
    QString pw=ui->edit_pw->text();
    //TODO检查该用户名、及记录用户是否存在还没写
   int result =DFile().userexist(name,pw);
    //如果该用户不存在，则注册写入用户表中
    if(result == 3){
        DFile().createUser(name,pw);
    }
    QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("注册成功！"));
    emit(confirm(name));
    this->close();
}
