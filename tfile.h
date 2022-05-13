#ifndef TFILE_H
#define TFILE_H
#include<QString>
#include<QDir>
#include<QFile>
#include <QDebug>
class TFile
{
public:
    TFile();
    static bool createTable(QString username,QString basename,QString tbname);


    static bool  tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);
//    static void writeFileTIC(QString str,QString user,QString kuname,QString biaoname);

    //表的详细日志
    static bool addTBRecord(int type, QString username, QString baseName, QString tbname, QString sql);
};

#endif // TFILE_H
