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
    qDebug()<<"result"<<result;
    QFile userf("D:/MyDataBase/ID.nf");
    userf.open(QIODevice::ReadWrite);
    QDataStream stream (&userf);
    //获取当前用户的权限
    QString str;
    QStringList rights;
    int flag=0;
    while(!stream.atEnd()){
        for(int i=0;i<6;i++){
            stream>>str;
            if(flag==1&&i>1){
                rights.push_back(str);
            }
            if(i==0&&str==name&&flag==0){
                flag=1;
            }
        }
        if(flag==1){
            break;
        }
    }
    if(result==1){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("登入成功！"));
        qDebug()<<rights[0]<<rights[1]<<rights[2]<<rights[3];
        emit(login(name,rights[0],rights[1],rights[2],rights[3]));//传递登入信号并传参
        this->close();
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("用户名或密码错误！"));

    }

}

//重置按钮
void LoginFrame::btn_reset_clicked(){
    ui->edit_name->clear();
    ui->edit_pw->clear();
}
//注册的登入传递信号
void LoginFrame::reg_login(QString name,QString dba,QString create,QString update,QString dele){
    emit(login(name,dba,create,update,dele));
    this->close();
}
//注册按钮
void LoginFrame::btn_regist_clicked(){
    rf=new RegistFrame();
    rf->show();
    connect(rf,SIGNAL(confirm(QString,QString,QString,QString,QString)),this,SLOT(reg_login(QString,QString,QString,QString,QString)));
}
