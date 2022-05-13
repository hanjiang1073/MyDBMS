#ifndef SQL_H
#define SQL_H
#include <QWidget>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFile>
#include<dfile.h>
#include<tfile.h>

class SQL
{
public:
    SQL();
    QString user;//当前用户

    QTreeWidgetItem *kuItem=NULL;
    QTreeWidgetItem *biaoItem=NULL;
    void CreateT(QString user,QString kuname ,QString biaoname);
    void CreateD(QString user,QString kuname);
    void CreateU(QString user,QString kuname);
    void InsertT(QString user,QString kuname,QString biaoname,QString type,QString value,QString mins,QString maxs,QString def);
    void TDesign(QString user,QString kuname,QString biaoname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);
};

#endif // SQL_H
