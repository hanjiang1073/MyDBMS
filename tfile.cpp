#include "tfile.h"
#include <QDataStream>
#include "recordinsert.h"
TFile::TFile()
{

}

bool TFile::deleteRecord(QString user, QString kuname, QString biaoname, int recordRow)
{
    QString recdir = "D:/MyDataBase/"+ user+'/' + kuname+'/'+biaoname;
    QString filename_tic = recdir + '/' + biaoname + ".tic";
    QFile tic(filename_tic);
    tic.seek(0);
    if(tic.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream rstream (&tic);
    QString rstr;
    QStringList rstrlist;
    int m=0;
    //取出各记录除选中记录外
    while(!rstream.atEnd()){
        rstream>>rstr;
        if(m==recordRow){
            m++;
            continue;
        }else{
            qDebug()<<"rstr"<<rstr;
            rstrlist.append(rstr);
        }
        m++;
    }
    tic.close();
    qDebug()<<"rstrlist"<<rstrlist;
    //重新写入
    QFile wtic(filename_tic);
    wtic.open(QFile::WriteOnly|QIODevice::Truncate);//先清空
    wtic.open(QFile::Append);
    wtic.seek(0);
    QDataStream wstream (&wtic);
    for(int i=0;i<rstrlist.size();i++){
        wstream<<rstrlist[i];
    }
    wtic.close();
    return true;
}

bool TFile::tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool un,bool non,QString com)

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
qDebug()<<name+"|"+type+"|"+len+"|"+def+"|"+min+"|"+max+"|"+pk1+"|"+un1+"|"+non1+"|"+com;
    stream<<name+"|"+type+"|"+len+"|"+def+"|"+min+"|"+max+"|"+pk1+"|"+un1+"|"+non1+"|"+com;
    tdf.close();
    return true;
}

//写入tic文件
bool TFile::writeFileTIC(QString user,QString kuname,QString biaoname,QString str){
    QString dirname = "D:/MyDataBase/"+ user+'/' + kuname+'/'+biaoname;
    QString filename_tic = dirname + '/' + biaoname + ".tic";
    QFile tic(filename_tic);
    tic.open(QIODevice::Append);
    QDataStream stream (&tic);
    stream<<str;
    return true;
}

//添加表日志
bool TFile::addTBRecord(int type, QString username, QString baseName, QString tbname,QString sql)
{
    return true;
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
//        stream<<username+" "+basename+" "+tbname;
        /*stream1<<username+" "+basename+" "+tbname;
        stream2<<username+" "+basename+" "+tbname;
        stream3<<username+" "+basename+" "+tbname;*/
        tdf.close();
        trd.close();
        tic.close();
        tid.close();
        return true;

    }
    else{
          return false;
        //报错
    }
}

//bool TFile::modifytabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com)
//{
//    QString pk1= QString::number(pk);
//    QString non1=QString::number(non);
//    QString un1=QString::number(un);
//    modifystr=name+"|"+type+"|"+len+"|"+def+"|"+min+"|"+max+"|"+pk1+"|"+non1+"|"+un1+"|"+com;
//}
