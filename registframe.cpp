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
    //检查该用户名、及记录用户是否存在还没写
    QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("注册成功！"));
    emit(confirm());
    this->close();
}
