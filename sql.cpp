#include "sql.h"
#include <QDateTime>
SQL::SQL()
{

}
void SQL::CreateT(QString user,QString kuname ,QString biaoname)
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    QString str="create table "+biaoname;//生成语句
    TFile().createTable(user,kuname,biaoname);
    QString logName = "D:/MyDataBase/" + user + "/" + kuname +"/" +biaoname+"/"+biaoname + ".trd";
    QFile log (logName);
    log.open(QIODevice::Append);
    QDataStream stream (&log);
      stream<<str1+str;
      log.close();
     /*Logic lo=new Logic();
     lo.user=user;
     lo.kuname=kuname;
     lo.biaoname=biaoname;
     lo.Check(str);
     */



}
void SQL::InsertT(QString user,QString kuname ,QString biaoname,QString type,QString value,QString mins,QString maxs,QString def)
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    QString str="insert into table "+biaoname+" values ("+value+mins+maxs+def+")";
    QString logName = "D:/MyDataBase/" + user + "/" + kuname +"/" +biaoname+"/" +biaoname+ ".trd";
    QFile log (logName);
    log.open(QIODevice::Append);
    QDataStream stream (&log);
     stream<<str1+str;
     log.close();
}

void SQL::CreateD(QString user,QString kuname)
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
   QString str="create database "+kuname;
     DFile().createDataBase(kuname,user);
    QString filename = "D:/MyDataBase/" + user + "/" + kuname +"/" +kuname + ".log";
       QFile logf(filename);
       bool logo = logf.open(QIODevice::ReadWrite);
        QDataStream stream1(&logf);
        stream1<<str1+str;
        logf.close();
       /*Logic lo=new Logic();
       lo.user=user;
       lo.kuname=kuname;
       lo.Check(str);*/




}
void SQL::CreateU(QString user,QString kuname)
{
    QString dirname = "D:/MyDataBase/"+user+"/" + kuname;
       QString filename2 =dirname+'/'+kuname +".log";
       QFile logf(filename2);
        QDataStream stream1(&logf);
       QString str="create table "+user;
      /* Logic lo=new Logic();
       lo.user=user;
       lo.kuname=kuname;
       lo.Check(str);
     */

}
void SQL::TDesign(QString user,QString kuname, QString biaoname, QString name, QString type, QString len, QString def, QString min, QString max, bool pk, bool non, bool un, QString com)
{
     QString str="alter table "+biaoname+" add "+name+type+"("+len+")";
     if(def!=nullptr)
     {
          str.append(" default "+def);
     }
     if(pk==true)
      {
         str.append(" primary key");
     }
     if(non==true)
      {
         str.append(" not null");
     }
     if(un==true)
      {
       str.append(" unqiue");
     }
     if(min!=nullptr||max!=nullptr)
     {
         str.append(" check("+name+">="+min+"and"+name+"<="+max+")");
     }

     if(com!=nullptr)
     {
        str.append(" //"+com);
     }
     /*Logic lo=new Logic();
     lo.user=user;
     lo.kuname=kuname;
     lo.biaoname=biaoname;
     lo.Check(str);*/
     QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
     QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
     TFile().tabledesign(user,kuname,biaoname,name,type,len,def,min,max,pk,non,un,com);
     QString logName = "D:/MyDataBase/" + user+ "/" + kuname +"/" +biaoname+"/" +biaoname  + ".trd";
     QFile log (logName);
     log.open(QIODevice::Append);
     QDataStream stream (&log);
     stream<<str1+str;
     log.close();

}

