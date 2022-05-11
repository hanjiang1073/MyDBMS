#include "tfile.h"
#include <QDataStream>
TFile::TFile()
{

}

bool TFile::tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com)

{
    QString dirname = "D:/MyDataBase/"+ username+'/' + basename+'/'+tbname;
    QString filename_tdf = dirname + '/' + tbname + ".tdf";
     //表定义文件

    QFile tdf(filename_tdf);
    tdf.open(QIODevice::Append);
    QDataStream stream (&tdf);

    QString pk1= QString::number(pk);
    QString non1=QString::number(non);
    QString un1=QString::number(un);
qDebug()<<name+"|"+type+"|"+len+"|"+def+"|"+min+"|"+max+"|"+pk1+"|"+non1+"|"+un1+"|"+com;
    stream<<name+"|"+type+"|"+len+"|"+def+"|"+min+"|"+max+"|"+pk1+"|"+non1+"|"+un1+"|"+com;
    tdf.close();
    return true;
}


//添加表日志
bool TFile::addTBRecord(int type, QString username, QString baseName, QString tbname，QString sql)
{

}

bool TFile::createTable(QString username,QString basename,QString tbname)

{

    QString dirname = "D:/MyDataBase/"+ username+'/' + basename+'/'+tbname;
    QString filename_tdf = dirname + '/' + tbname + ".tdf";
    QString filename_trd = dirname + '/' + tbname + ".trd";
    QString filename_tic = dirname + '/' + tbname + ".tic";
    QString filename_tid = dirname + '/' + tbname + ".tid";
    //表文件夹
    QDir dir(dirname);
    //表定义文件
    QFile tdf(filename_tdf);
    //表日志文件
    QFile trd(filename_trd);
    //表内容文件
    QFile tic(filename_tic);
    //表索引文件
    QFile tid(filename_tid);

    if(!dir.exists()){
        dir.mkdir(dirname);
        tdf.open(QIODevice::ReadWrite);
        trd.open(QIODevice::ReadWrite);
        tic.open(QIODevice::ReadWrite);
        tid.open(QIODevice::ReadWrite);
        QDataStream stream (&tdf);
        QDataStream stream1 (&trd);
        QDataStream stream2 (&tic);
        QDataStream stream3 (&tid);
        stream<<username+" "+basename+" "+tbname;
        /*stream1<<username+" "+basename+" "+tbname;
        stream2<<username+" "+basename+" "+tbname;
        stream3<<username+" "+basename+" "+tbname;*/
        tdf.close();
        trd.close();
        tic.close();
        tid.close();
        return true;

    }
}
