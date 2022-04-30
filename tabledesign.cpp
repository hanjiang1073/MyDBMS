#include "tabledesign.h"
#include "ui_tabledesign.h"

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

        //关闭窗口
        this->close();

    }
}
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
