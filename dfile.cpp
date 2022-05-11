#include "dfile.h"
#include <QDateTime>
//对数据库文件进行操作的类
DFile::DFile()
{

}

//返回2是已存在，返回1是创建失败，返回0是创建成功
int DFile::createDataBase(QString baseName,QString username)
{
    //this->baseName = baseName;
    //数据库文件夹
    QString dirname = "D:/MyDataBase/"+username+"/" + baseName;
    //db文件
    QString filename1 =dirname+'/'+baseName +".db";
    //log文件
    QString filename2 =dirname+'/'+baseName +".log";
    QDir dir(dirname);
    QFile dbf(filename1);
    QFile logf(filename2);
    if(!dir.exists()){
        dir.mkdir(dirname);
       bool dbo= dbf.open(QIODevice::ReadWrite);
       bool logo = logf.open(QIODevice::ReadWrite);

       if(!dbo || !logo){

           dbf.close();
           logf.close();
           return 1;
       }
       else{
           QDataStream stream(&dbf);
           QDataStream stream1(&logf);
           QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
           QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间          
           stream<<username+" "+baseName+" "+str;
           dbf.close();
           logf.close();
           return 0;
       }
    }
    else{
        return 2;
    }

}

//返回true初始化成功
bool DFile::initialDataBase()
{

    QDir dir0("D:/MyDataBase");
    qDebug()<<dir0.exists()<<"here";
    if(!dir0.exists()){
        dir0.mkdir("D:/MyDataBase");
    }


    QDir dir("D:/MyDataBase/ORIGIN");
    QFile userf("D:/MyDataBase/ID.nf");
    QFile dbf("D:/MyDataBase/ORIGIN/origin.db");
    QFile logf("D:/MyDataBase/ORIGIN/origin.log");


    if(!dir.exists()){
        dir.mkdir("D:/MyDataBase/ORIGIN");
       bool dbo= dbf.open(QIODevice::ReadWrite);
       bool logo = logf.open(QIODevice::ReadWrite);
       bool ufo = userf.open(QIODevice::ReadWrite);


       if(!dbo || !logo || !ufo ){

           return false;
       }
       else{

           dbf.close();
           logf.close();
           userf.close();
           return true;
       }
    }
    else{
        return true;
    }


}


//返回true创建成功，false表示已存在用户
bool DFile::createUser(QString username, QString secret)
{
    QFile userf("D:/MyDataBase/ID.nf");
    userf.open(QIODevice::ReadWrite);
    QDataStream stream (&userf);

    stream << username;
    stream << secret;

    userf.close();

    QString dirname = "D:/MyDataBase/" + username;
    QString recname = "D:/MyDataBase/" + username + "/" + username + ".rec";
    QDir dir(dirname);
    QFile rec(recname);
    if(!dir.exists()){
        dir.mkdir(dirname);
        rec.open(QIODevice::ReadWrite);
        rec.close();
        return true;
    }
    else{
        return false;
    }
}


//返回1表示账号密码都对，返回2表示账号对密码不对，返回3是不存在用户
int DFile::userexist(QString username, QString secret)
{
    QFile userf("D:/MyDataBase/ID.nf");
    userf.open(QIODevice::ReadWrite);
    QDataStream stream (&userf);

    QString ID;
    QString scrt;

    while(!stream.atEnd()){
        stream >> ID;
        stream >> scrt;
        if(ID==username){
            if(scrt==secret){
                return 1;
            }
            else{return 2;}
        }
        else{
            continue;
        }
    }
    return 3;
}

//获取当前时间
QString DFile::currentTime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    return current_date;
}


//用户库操作的记录
bool DFile::addRecord(int type, QString username, QString baseName)
{
    QString recName = "D:/MyDataBase/" + username + "/" + username + ".rec";
    QFile rec(recName);
    rec.open(QIODevice::Append);
    QDataStream stream(&rec);
    QString msg;
    switch (type) {
    case 1:
          msg = currentTime() + "create database " + baseName + " by " + username;
          stream << msg;
          return true;
    case 2:
          msg = currentTime() + "operate database " + baseName + " by " + username;
          stream << msg;
          return true;
    case 3:
          msg = currentTime() + "delete database " + baseName + " by " + username;
          stream << msg;
          return true;
    default:
        return false;
    }

}


//添加库表记录
bool DFile::addDBRecord(int type, QString username, QString baseName, QString tbname)
{
    QString logName = "D:/MyDataBase/" + username + "/" + baseName +"/" +baseName + ".log";
    QFile log (logName);
    log.open(QIODevice::Append);
    QDataStream stream (&log);
    QString msg;
    switch (type) {
    //创建表
    case 1:
        msg = currentTime() + " create table " + tbname + " in " + baseName;
        stream << msg;
        return true;
    //操作表
    case 2:
        msg = currentTime() + " operate table " + tbname + " in " + baseName;
        stream << msg;
        return true;
    //删除表
    case 3:
        msg = currentTime() + " delete table " + tbname + " in " + baseName;
        stream << msg;
        return true;

    default:
        return false;

    }
}


