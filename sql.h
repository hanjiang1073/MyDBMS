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
    void GrantU(QString user,QString kuname ,QString biaoname,QString dba,QString createright,QString updateright, QString deleright);//用户授权
    void deleteT(QString user,QString kuname ,QString biaoname);
    void deleteField(QString user,QString kuname,QString biaoname,QString name);//删除字段
    void ModifyDesign(QString user,QString kuname ,QString biaoname,QString prevname,QString str2);//修改字段
    void Logic(QString sql,QString user,QString kuname,QString biaoname);//sql语句识别
    void InsertT(QString user,QString kuname,QString biaoname,QString str2);//向表插入数据
    void TDesign(QString user,QString kuname,QString biaoname,QString name,QString type,QString len,QString def,QString min,QString max,bool pk,bool non,bool un,QString com);
    void deleteRecord(QString user,QString kuname ,QString biaoname,int);//生成删除记录

};

#endif // SQL_H
