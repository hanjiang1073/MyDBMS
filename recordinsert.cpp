#include "recordinsert.h"
#include "ui_recordinsert.h"
#include <QDataStream>
#include "sql.h"
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
    QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tdf = dirname + '/' + tablename + ".tdf";
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
        int RowCont=ui->tableWidget->rowCount();
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
                    if(j==6){
                        pks.push_back(RowCont);
                    }
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
    QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tic = dirname + '/' + tablename + ".tic";
    QFile tic(filename_tic);
    tic.open(QIODevice::Append);
    QDataStream stream (&tic);
    stream<<str;
}

//修改label标签
void RecordInsert::changeLabel(QString text){
    ui->label->setText(text);
}
//确认按钮
void RecordInsert::on_button_confirm(){
    int row=ui->tableWidget->rowCount();
    int flag=1;//不妨用1表示合法，2表示违反类型约束，3表示违反检查约束,4不符合键约束
    int wrongRow=-1;
    QString str;
    //判断当前插入的记录是否合法
    for(int i=0;i<row;i++){
        QString name=ui->tableWidget->item(i,0)->text();//字段名
        QString type=ui->tableWidget->item(i,1)->text();//字段类型
        QString value=ui->tableWidget->item(i,9)->text();//要插入的值
        QString mins=ui->tableWidget->item(i,4)->text();//最大值（QString）
        QString maxs=ui->tableWidget->item(i,5)->text();//最小值（QString）
        QString def=ui->tableWidget->item(i,3)->text();//默认值
        QString length=ui->tableWidget->item(i,2)->text();//字段长度
        int pk=0,uk=0,nk=0;//主键，唯一键，非空
        if(ui->tableWidget->item(i,6)!=NULL){
            pk=1;
        }
        if(ui->tableWidget->item(i,7)!=NULL){
            uk=1;
        }
        if(ui->tableWidget->item(i,8)!=NULL){
            nk=1;
        }
        std::string svalue=value.toStdString();
        if(type=="Integer"){
            //判断是否是Integer类型
            if(svalue.find('.')!=-1||checkdigit(svalue)==false){
                flag=2;
                wrongRow=i;
                break;
            }
            int num=std::stoi(svalue);
            qDebug()<<"num"<<num;
            //判断是否符合最大值最小值
            if(mins!="NULL"){
                double minn=mins.toDouble();
                if(num<minn){
                    flag=3;
                    wrongRow=i;
                    break;
                }
            }
            if(maxs!="NULL"){
                double maxn=maxs.toDouble();
                if(num>maxn){
                    flag=3;
                    wrongRow=i;
                    break;
                }
            }
        }
        if(type=="Float"){
            //判断是否是浮点数
            if(checkdigit(svalue)==false){
                flag=2;
                wrongRow=i;
                break;
            }
            double num=std::stof(svalue);
            //判断是否符合最大值最小值
            if(mins!="NULL"){
                double minn=mins.toDouble();
                if(num<minn){
                    flag=3;
                    wrongRow=i;
                    break;
                }
            }
            if(maxs!="NULL"){
                double maxn=maxs.toDouble();
                if(num>maxn){
                    flag=3;
                    wrongRow=i;
                    break;
                }
            }
        }
        if(type=="Boolean"){
            if(value=="true"||value=="True"||value=="TRUE"){
                value="1";
            }
            if(value=="false"||value=="False"||value=="FALSE"){
                value="0";
            }
            if(value!='1'&&value!='0'){
                flag=2;
                wrongRow=i;
                break;
            }
        }
        if(type=="Varchar"){
            if(length!="NULL"){
                double len=length.toDouble();
                if(value.size()>len){
                    flag=3;
                    wrongRow=i;
                    break;
                }
            }
        }

        //如果当前值为空有默认值则补上默认值
        if(value==""){
            if(def!="NULL"){
                str.append(def);
                if(i!=row-1){
                    str.append("|");
                }
            }else{
                if(pk==1||nk==1){
                    flag=4;
                    wrongRow=i;
                    break;
                }else{
                    str.append("NULL");
                    if(i!=row-1){
                        str.append("|");
                    }
                }
            }
        }
        else{
            bool check=true;
            if(pk==1||uk==1){
                check=checkUnique(value,i);
            }
            if(check==true){
                str.append(value);
                if(i!=row-1){
                    str.append("|");
                }
            }else{
                flag=4;
                wrongRow=i;
                break;
            }

        }
    }
    if(flag==1){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("插入成功！"));
        SQL().InsertT(user,databasename,tablename,str);//在此生成SQL语句
        writeFile(str);
    }else{
        qDebug()<<"wrongRow"<<wrongRow;
        std::string prompt="第";
        prompt+=std::to_string(wrongRow+1);
        switch(flag){
            case 2:
                prompt+="行违反了类型约束";
                QMessageBox::information(this, QStringLiteral("提示"),QString::fromLocal8Bit(prompt.c_str()));
                break;
            case 3:
                prompt+="行违反了检查约束";
                QMessageBox::information(this, QStringLiteral("提示"),QString::fromLocal8Bit(prompt.c_str()));
                break;
            case 4:
                prompt+="行违反了键约束";
                QMessageBox::information(this, QStringLiteral("提示"),QString::fromLocal8Bit(prompt.c_str()));
                break;
            default:
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

//判断你是否唯一
bool RecordInsert::checkUnique(QString value,int row){
    QString rdirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tic = rdirname + '/' + tablename + ".tic";
    QFile tic(filename_tic);
    tic.seek(0);
    if(tic.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream rstream (&tic);
    QStringList recordList;
    QString records;
    while(!rstream.atEnd()){
        rstream>>records;
        recordList=records.split("|");
        //如果当前插入的记录值与已存在记录值相同则返回false
        if(recordList[row]==value){
            tic.close();
            return false;
        }
    }
    return true;
}
