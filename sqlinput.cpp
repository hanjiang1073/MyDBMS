#include "sqlinput.h"
#include "ui_sqlinput.h"

SqlInput::SqlInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlInput)
{
    ui->setupUi(this);
}

SqlInput::~SqlInput()
{
    delete ui;
}

//sql语句解析
void SqlInput::sqlTran(QString str){
    qDebug()<<str;
    QStringList list=str.split(" ");//按空格将sql语句分割
    //创建库
    if(list[0]=="create"){
        SQL().CreateD(this->user,list[2]);
        DFile().addRecord(1,user,list[2]);
    }
    //选择库
    if(list[0]=="alter"){
        databasename=list[2];
        //建表
        if(list[3]=="create"){
            SQL().CreateT(this->user,databasename,list[5]);
            DFile().addDBRecord(1,this->user,databasename,list[5]);
        }
        //删除表
        if(list[3]=="drop"){

        }
        //选择表
        if(list[3]=="table"){
            tablename=list[4];
            //增加字段
            if(list[5]=="add"){
                QString field=list[6];
                QStringList fieldlist=field.split("|");
                QString name=fieldlist[0];
                QString type=fieldlist[1];
                QString len=fieldlist[2];
                QString def=fieldlist[3];
                QString min=fieldlist[4];
                QString max=fieldlist[5];
                bool pk=fieldlist[6]=="1"?true:false;
                bool un=fieldlist[7]=="1"?true:false;
                bool non=fieldlist[8]=="1"?true:false;
                QString com=fieldlist[9];
                SQL().TDesign(this->user,databasename,tablename,name,type,len,def,min,max,pk,un,non,com);
            }
            //增加记录
            if(list[5]=="insert"){
                SQL().InsertT(user,databasename,tablename,list[6]);//在此生成SQL语句
                TFile().writeFileTIC(this->user,databasename,tablename,list[6]);
            }
            //条件查询
            if(list[5]=="select"){

            }
        }

    }
    //删除库
    if(list[0]=="drop"){

    }
}
//重置按钮
void SqlInput::reset(){
    ui->plainTextEdit->clear();
}

//确认按钮
void SqlInput::confirm(){
    QString sqls=ui->plainTextEdit->toPlainText();//将所有sql文本转换成字符串
    QStringList sqlList=sqls.split("\n");//按行来分割
    for(int i=0;i<sqlList.size();i++){
        sqlTran(sqlList[i]);
    }
    this->close();
}

//导入文件
void SqlInput::inputFile(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setNameFilter(tr("File(*.txt*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    //获取选择的文件路径
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }

    //获取选择到的文件
    QFile inputFile(fileNames[0]);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        QTextStream in(&inputFile);  //用文件构造流
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            sqlTran(line);
            line=in.readLine();//循环读取下行
        }
    }
    inputFile.close();
    this->close();
}
