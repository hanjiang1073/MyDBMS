#include "tabledesign.h"
#include "ui_tabledesign.h"
#include "tfile.h"
TableDesign::TableDesign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableDesign)
{
    ui->setupUi(this);
    ui->lenEdit->setDisabled(true);

}

TableDesign::~TableDesign()
{
    delete ui;
}
//主键选择
void TableDesign::on_checkBox_pkc(){
    //选择主键，唯一非空键自动选上
    if(ui->pkCheck->isChecked()){

        ui->unCheck->setChecked(true);
        ui->nonCheck->setChecked(true);
    }
}
<<<<<<< HEAD

=======
>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a
//字段类型comboBox选项设置
void TableDesign::on_comboBox_CIC(const QString &arg){
    //如果选的是Integer或Float 字段长度一栏不可填
    if(arg=="Integer"||arg=="Float"){
        ui->maxnEdit->setEnabled(true);
        ui->minnEdit->setEnabled(true);
        ui->lenEdit->clear();
        ui->lenEdit->setDisabled(true);
    }
    //如果选的是Varchar，最大值最小值不可填
    if(arg=="Varchar"){
        ui->maxnEdit->clear();
        ui->minnEdit->clear();
        ui->maxnEdit->setDisabled(true);
        ui->minnEdit->setDisabled(true);
        ui->lenEdit->setEnabled(true);
    }
    //如果是boolean最大最小字段长度都不可填
    if(arg=="Boolean"){
        ui->lenEdit->clear();
        ui->maxnEdit->clear();
        ui->minnEdit->clear();
        ui->maxnEdit->setDisabled(true);
        ui->minnEdit->setDisabled(true);
        ui->lenEdit->setDisabled(true);
    }
}

//确认
void TableDesign::on_button_confirm(){
    //除了字段名称不为空其余都可为空（字段类型是combobox没有空值）
    //TODO需要判断是否同名
    if(ui->nameEdit->text()==""){
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("字段名称不能为空！"));
    }else{
        //TODO将字段信息写入文件,根据属性user，biaoItem指向的是插入字段的那张表存的时候需要使用
        QString str1=ui->nameEdit->text();
        QString str2=ui->comEdit->toPlainText();
        QString str3=ui->lenEdit->text();
        QString str4=ui->defaultEdit->text();
        QString str5=ui->minnEdit->text();
        QString str6=ui->maxnEdit->text();
         QString str7=ui->typeButton->currentText();
        bool t1=ui->pkCheck->isChecked();
        bool t2=ui->nonCheck->isChecked();
        bool t3=ui->unCheck->isChecked();
<<<<<<< HEAD
        if(str2=="")
        {
            str2="NULL";
qDebug()<<"com为空";
        }
        if(str3=="")
        {
            str3="NULL";
qDebug()<<"len为空";
        }
        if(str4=="")
        {
            str4="NULL";
qDebug()<<"def为空";
        }
        if(str5=="")
        {
            str5="NULL";
qDebug()<<"min为空";
        }
        if(str6=="")
        {
            str6="NULL";
qDebug()<<"max为空";
        }


        TFile::tabledesign(this->user,this->kuname,this->biaoItem->text(0),str1,str7,str3,str4,str5,str6,t1,t2,t3,str2);
        //关闭窗口
        this->close();
qDebug()<<"user:"<<user;
    }
}

=======
        TFile::tabledesign(this->user,this->kuname,this->biaoItem->text(0),str1,str7,str3,str5,str6,t1,t2,t3,str2,str4);
        //关闭窗口
        this->close();

    }
}
>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a
//重置按钮
void TableDesign::on_button_reset(){
    ui->nameEdit->clear();
    ui->comEdit->clear();
    ui->lenEdit->clear();
    ui->defaultEdit->clear();
    ui->minnEdit->clear();
    ui->maxnEdit->clear();
    ui->pkCheck->setChecked(false);
    ui->nonCheck->setChecked(false);
    ui->unCheck->setChecked(false);
}

