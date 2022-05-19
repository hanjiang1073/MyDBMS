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

    QTreeWidgetItem *databaseItem=NULL;
    QTreeWidgetItem *tableItem=NULL;
    void CreateT(QString user,QString databasename ,QString tablename);
    void CreateD(QString user,QString databasename);
    void CreateU(QString user,QString databasename);
    void GrantU(QString user,QString dba,QString createright,QString updateright, QString deleright);//用户授权
    void deleteT(QString user,QString databasename ,QString tablename);
    void deleteField(QString user,QString databasename,QString tablename,QString name);//删除字段
    void ModifyDesign(QString user,QString databasename ,QString tablename,QString prevname,QString str2);//修改字段
    void Logic(QString sql,QString user,QString databasename,QString tablename);//sql语句识别
    void InsertT(QString user,QString databasename,QString tablename,QString str2);//向表插入数据
    void TDesign(QString user,QString databasename,QString tablename,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);
    void deleteRecord(QString user,QString databasename ,QString tablename,int);//生成删除记录

};

#endif // SQL_H
