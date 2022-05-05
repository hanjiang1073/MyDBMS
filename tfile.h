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



};

#endif // TFILE_H
