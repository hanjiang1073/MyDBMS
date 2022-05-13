#include "queryframe.h"
#include "ui_queryframe.h"

QueryFrame::QueryFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryFrame)
{
    ui->setupUi(this);
}

QueryFrame::~QueryFrame()
{
    delete ui;
}

//查询界面
void QueryFrame::showWidget(){
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("字段")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("值")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qDebug()<<"query"<<biaoname<<kuname;
    QString dirname = "D:/MyDataBase/"+ user+'/' + kuname+'/'+biaoname;
    QString filename_tdf = dirname + '/' + biaoname + ".tdf";
    QFile tdf(filename_tdf);
    tdf.seek(0);
    if(tdf.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream stream (&tdf);
    QString str;
    QStringList strlist;
    if(stream.atEnd()){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该表不存在字段！"));
        this->close();
    }
    int row=0;
    //将值分解后写入单元格
    while(!stream.atEnd()){
        row=ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);
        stream>>str;
        strlist=str.split("|");
        qDebug()<<strlist[0];
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(strlist[0]));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem());
    }
    tdf.close();
}

//确认按钮
void QueryFrame::confirm(){
    int row=ui->tableWidget->rowCount();
    qDebug()<<"confirmhere"<<row;
    QString str;//str记录要查询的值以及对应字段下标用|分割
    for(int i=0;i<row;i++){
        QString value=ui->tableWidget->item(i,1)->text();
        qDebug()<<value;
        if(value==""){
            qDebug()<<i;
        }else{
            str.append(QString::number(i));
            str.append(value);
            str.append("|");
        }
    }
    str.chop(1);//删除最后的分隔符|
    qDebug()<<str;
    emit(submit(str));
    this->close();
}
