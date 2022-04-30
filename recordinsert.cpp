#include "recordinsert.h"
#include "ui_recordinsert.h"

RecordInsert::RecordInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordInsert)
{
    ui->setupUi(this);
    initTableWidget();
}

RecordInsert::~RecordInsert()
{
    delete ui;
}

//初始化tablewidget
void RecordInsert::initTableWidget(){
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("字段名")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("字段类型")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("长度")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QString::fromLocal8Bit("主键")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QString::fromLocal8Bit("唯一键")));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem(QString::fromLocal8Bit("非空")));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem(QString::fromLocal8Bit("值")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //TODO通过biaoItem读取这张表的字段信息
    if(1){

    }else{
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("该表不存在字段！"));
        this->close();
    }
}

//确认按钮
void RecordInsert::on_button_confirm(){
    int flag=1;//不妨用1表示合法，2,3,4...表示违反了什么错误，例如2表示违反了主键约束
    //TODU读取文件确认主键、最小值最大值唯一性非空性是否满足
    if(flag==1){
        //TODO写入文件

        this->close();
    }else{
        switch(flag){
            default:
                QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("违反了完整性约束!"));
                break;
        }
    }
}

//重置按钮
void RecordInsert::on_button_reset(){
    int row=ui->tableWidget->rowCount();//首先获取有多少行然后每个行一个个删

}
