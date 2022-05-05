#include "dfile.h"
#include <QDateTime>
//对数据库文件进行操作的类
DFile::DFile()
{

<<<<<<< HEAD
=======

>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a
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
           stream<<username+" "+baseName;
           stream1<<username+" "+baseName+" "+str;
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

<<<<<<< HEAD
    userf.close();

=======
>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a
    QString dirname = "D:/MyDataBase/" + username;
    QDir dir(dirname);
    if(!dir.exists()){
        dir.mkdir(dirname);
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
