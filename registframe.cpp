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

//dba键连带作用
void RegistFrame::on_checkBox_dba(){
    //选择dba，默认选上其他的
    if(ui->dbaCheck->isChecked()){

        ui->createCheck->setChecked(true);
        ui->deleteCheck->setChecked(true);
        ui->updateCheck->setChecked(true);
    }
}
//注册确认
void RegistFrame::btn_confirm_clicked(){
    QString name=ui->edit_name->text();
    QString pw=ui->edit_pw->text();
    QString dba=ui->dbaCheck->isChecked()?"1":"0";//管理员权限
    QString create=ui->createCheck->isChecked()?"1":"0";//创建权限
    QString update=ui->updateCheck->isChecked()?"1":"0";//修改权限
    QString dele=ui->deleteCheck->isChecked()?"1":"0";//删除权限
    bool check_dba=true;
    if(dba=="1"){
        check_dba=DFile().checkDBA();
    }
    if(check_dba==false){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("已存在DBA！"));
        return;
    }
    //TODO检查该用户名、及记录用户是否存在还没写
   int result =DFile().userexist(name,pw);
    //如果该用户不存在，则注册写入用户表中
    if(result == 3){
        DFile().createUser(name,pw,dba,create,update,dele);
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该用户已存在！"));
    }
    QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("注册成功！"));
    emit(confirm(name));
    this->close();
}
