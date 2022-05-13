#include "recordinsert.h"
#include "ui_recordinsert.h"
#include <QDataStream>
RecordInsert::RecordInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordInsert)
{
    ui->setupUi(this);

}

RecordInsert::~RecordInsert()
{
    delete ui;
}

//初始化tablewidget
void RecordInsert::initTableWidget(){
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("字段名")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("字段类型")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("长度")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("默认值")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("最小值")));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem(QStringLiteral("最大值")));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem(QStringLiteral("主键")));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem(QStringLiteral("唯一键")));
    ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem(QStringLiteral("非空")));
    ui->tableWidget->setHorizontalHeaderItem(9,new QTableWidgetItem(QStringLiteral("值")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    int i=0;
    if(stream.atEnd()){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该表不存在字段！"));
        this->close();
    }
    //将值分解后写入单元格
    while(!stream.atEnd()){
        qDebug()<<"进入循环了！";
        int RowCont;
        RowCont=ui->tableWidget->rowCount();
//qDebug()<<"RowCont:"<<RowCont;
        ui->tableWidget->setRowCount(RowCont+1);//增加一行
        stream>>str;

        strlist=str.split("|");
        for(int j=0;j<=8;j++)
        {
            if(j==6||j==7||j==8)
            {
                if(strlist[j]=="1")
                {
                    QTableWidgetItem *citem=new QTableWidgetItem();
                    QIcon icon;
                    icon.addPixmap(QPixmap(":/pic/choose.jpg"));
                    citem->setTextAlignment(Qt::AlignCenter);
                    citem->setIcon(icon);
                    ui->tableWidget->setItem(i,j,citem);
                }
            }else
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(strlist[j]));
            }

        }
        i++;
    }
    tdf.close();
}

//写入文件
void RecordInsert::writeFile(QString str){
    QString dirname = "D:/MyDataBase/"+ user+'/' + kuname+'/'+biaoname;
    QString filename_tic = dirname + '/' + biaoname + ".tic";
    QFile tic(filename_tic);
    tic.open(QIODevice::Append);
    QDataStream stream (&tic);
    stream<<str;
}

//确认按钮
void RecordInsert::on_button_confirm(){
    int row=ui->tableWidget->rowCount();
    int flag=1;//不妨用1表示合法，2表示违反类型约束，3表示违反检查约束
    int wrongRow=-1;
    QString str;
    for(int i=0;i<row;i++){
        QString type=ui->tableWidget->item(i,1)->text();
        QString value=ui->tableWidget->item(i,9)->text();
        QString mins=ui->tableWidget->item(i,4)->text();
        QString maxs=ui->tableWidget->item(i,5)->text();
        QString def=ui->tableWidget->item(i,4)->text();
        /*
         *
         *以下是部分完整性检查的实现误删！
         *
         *
         */
//        std::string svalue=value.toStdString();
//        if(type=="Integer"){
//            if(svalue.find('.')||checkdigit(svalue)==0){
//                flag=2;
//                wrongRow=i;
//                break;
//            }
//            int num=std::stoi(svalue);
//            if(mins!="NULL"){
//                double minn=mins.toDouble();
//                if(num<minn){
//                    flag=3;
//                    wrongRow=i;
//                    break;
//                }
//            }
//            if(maxs!="NULL"){
//                double maxn=maxs.toDouble();
//                if(num>maxn){
//                    flag=3;
//                    wrongRow=i;
//                    break;
//                }
//            }
//        }
//        if(type=="Float"){
//            if(checkdigit(svalue)==false){
//                flag=2;
//                wrongRow=i;
//                break;
//            }
//            int num=std::stof(svalue);
//            if(mins!="NULL"){
//                double minn=mins.toDouble();
//                if(num<minn){
//                    flag=3;
//                    wrongRow=i;
//                    break;
//                }
//            }
//            if(maxs!="NULL"){
//                double maxn=maxs.toDouble();
//                if(num>maxn){
//                    flag=3;
//                    wrongRow=i;
//                    break;
//                }
//            }
//        }
        if(value==""&&def=="NULL"){
            str.append("NULL");
            if(i!=row-1){
                str.append("|");
            }
        }
        else{
            str.append(value);
            if(i!=row-1){
                str.append("|");
            }
        }
    }

    //TODU读取文件确认主键、最小值最大值唯一性非空性是否满足
    if(flag==1){
        //TODO写入文件
        //qDebug()<<"write"<<endl;
        writeFile(str);
    }else{
        switch(flag){
            default:
                std::string prompt="第";
                prompt+=wrongRow;
                prompt+="行违反了完整性约束";
                QMessageBox::information(this, QStringLiteral("提示"),QString::fromLocal8Bit(prompt.c_str()));
                break;
        }
    }
    this->close();
}

//重置按钮
void RecordInsert::on_button_reset(){
    int row=ui->tableWidget->rowCount();//首先获取有多少行然后每个行一个个删
    for(int i=0;i<row;i++){
        ui->tableWidget->item(i,9)->setText("");
    }
}

//判断字符串是否为数字
bool RecordInsert::checkdigit(std::string svalue){
    for(int i=0;i<svalue.size();i++){
        if(std::isdigit(svalue[i])==0){
            return false;
        }
    }
    return true;
}
