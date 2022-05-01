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
    static void createTable(QString username,QString basename,QString tbname);


};

#endif // TFILE_H
