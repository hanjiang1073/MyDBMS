#include "tfile.h"

TFile::TFile()
{

}

void TFile::createTable(QString username,QString basename,QString tbname)
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
    //表记录文件
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
    }
    else{
        //报错
    }
}
