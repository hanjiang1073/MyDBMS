#include "dfile.h"

//对数据库文件进行操作的类
dfile::dfile()
{


}

void dfile::createDataBase(QString baseName)
{
    //this->baseName = baseName;
    //数据库文件夹
    QString dirname = "D:/MyDataBase/" + baseName;
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
       if(!dbo or !logo){
           //出错
       }
    }
    else{
        //出错
    }
}

void dfile::initialDataBase()
{
    QDir dir("D:/MyDataBase/ORIGIN");
    QFile dbf("D:/MyDataBase/ORIGIN/origin.db");
    QFile logf("D:/MyDataBase/ORIGIN/origin.log");
    if(!dir.exists()){
        dir.mkdir("D:/MyDataBase");
       bool dbo= dbf.open(QIODevice::ReadWrite);
       bool logo = logf.open(QIODevice::ReadWrite);
       if(!dbo or !logo){
           //出错
       }
    }
    else{
        //出错
    }
}
