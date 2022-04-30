#ifndef TFILE_H
#define TFILE_H
#include<QString>
#include<QDir>
#include<QFile>

class tfile
{
public:
    tfile(QString basename);
    void createTable(QString tbname);
private:
    QString basename;

};

#endif // TFILE_H
