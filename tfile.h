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

<<<<<<< HEAD
    static bool  tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);
=======
    static bool  tabledesign(QString username,QString basename,QString tbname,QString name,QString type,QString len,QString min,QString max,bool pk,bool non,bool un,QString com,QString def);
>>>>>>> a4c3023aef11e59184da49d261f354f286c2b08a


};

#endif // TFILE_H
