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
    static bool deleteRecord(QString username,QString basename,QString tbname,int recordrow);//删除表记录
    static bool  tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);

//    static bool modifytabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);

    //表的详细日志
    static bool addTBRecord(int type, QString username, QString baseName, QString tbname, QString sql);
    static bool writeFileTIC(QString user,QString kuname,QString biaoname,QString str);
};


#endif // TFILE_H
