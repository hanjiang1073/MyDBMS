#include "sql.h"
#include <QDateTime>
#include "recordinsert.h"
#include <QString>
SQL::SQL()
{

}
void SQL::ModifyDesign(QString user, QString kuname, QString biaoname, QString name, QString name1)//修改字段
{
       QString str="alter table "+biaoname+" rename column "+name+" to "+name1;//生成语句
        this->Logic(str,user,kuname,biaoname);
}

void SQL::CreateT(QString user,QString kuname ,QString biaoname)//创建表
{
    QString str="create table "+biaoname;//生成语句
      this->Logic(str,user,kuname,biaoname);




}
void SQL::deleteRecord(QString user, QString kuname, QString biaoname, int row)//删除记录
{
    QString str="delete table "+biaoname+" where row= "+ row;
     this->Logic(str,user,kuname,biaoname);
}


void SQL::deleteT(QString user, QString kuname, QString biaoname)//删除表
{
     QString str="drop table "+biaoname;
      this->Logic(str,user,kuname,biaoname);
}

void SQL::InsertT(QString user,QString kuname ,QString biaoname,QString name,QString value,QString str2/*表记录语句*/)//插入记录
{
    QString str="insert into table "+biaoname+" ( "+name+" ) "+" values ( "+value+" )";
    this->Logic(str,user,kuname,biaoname);
    RecordInsert().writeFile(str2,user,kuname,biaoname);

}

void SQL::CreateD(QString user,QString kuname)
{
    QString biaoname;
   QString str="create database "+kuname;
   this->Logic(str,user,kuname,biaoname);





}
void SQL::CreateU(QString user,QString kuname)
{
    QString dirname = "D:/MyDataBase/"+user+"/" + kuname;
       QString filename2 =dirname+'/'+kuname +".log";
       QFile logf(filename2);
        QDataStream stream1(&logf);
       QString str="create table "+user+";";


}
void SQL::TDesign(QString user,QString kuname, QString biaoname, QString name, QString type, QString len, QString def, QString min, QString max, bool pk, bool non, bool un, QString com)//向表插入字段
{
     QString str="alter table "+biaoname+" add "+name+" "+type+"("+len+")";
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
         str.append(" check("+name+">="+min+" and "+name+"<="+max+")");
     }

     if(com!=nullptr)
     {
        str.append(" //"+com);
     }


     this->Logic(str,user,kuname,biaoname);//解析sql语句
     TFile().tabledesign(user,kuname,biaoname,name,type,len,def,min,max,pk,non,un,com);


}
   void SQL::Logic(QString sql,QString user,QString kuname,QString biaoname)//解析SQL语句
   {
       QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
       QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
       QStringList list = sql.split(" ");//将语句分割
       int row=list.size();
     //逐个识别
       if(list[0]=="create")
       {
           if (list[1]=="table") {

                TFile().createTable(user,kuname,list[2]);
                QString logName = "D:/MyDataBase/" + user + "/" + kuname +"/" +biaoname+"/"+biaoname + ".trd";
                QFile log (logName);
                log.open(QIODevice::Append);
                QDataStream stream (&log);
                  stream<<str1+sql+";";
                  log.close();
              }
           if (list[1]=="database") {

                 DFile().createDataBase(kuname,user);
                 QString filename = "D:/MyDataBase/" + user + "/" + kuname +"/" +kuname + ".log";
                    QFile logf(filename);
                    bool logo = logf.open(QIODevice::ReadWrite);
                     QDataStream stream1(&logf);
                     stream1<<str1+sql+";";
                     logf.close();

              }

           }

       else if(list[0]=="insert")
       {
         QString vaules=list[9];
         QString name=list[6];
         QString logName = "D:/MyDataBase/" + user + "/" + kuname +"/" +biaoname+"/" +biaoname+ ".trd";
         QFile log (logName);
         log.open(QIODevice::Append);
         QDataStream stream (&log);
          stream<<str1+sql+";";
          log.close();

       }
       else if(list[0]=="alter")
       {
            if(list[3]=="rename")
            {
                QString logName = "D:/MyDataBase/" + user+ "/" + kuname +"/" +biaoname+"/" +biaoname  + ".trd";
                           QFile log (logName);
                           log.open(QIODevice::Append);
                           QDataStream stream (&log);
                           stream<<str1+sql+";";
                           log.close();
            }
           else
            {QString logName = "D:/MyDataBase/" + user+ "/" + kuname +"/" +biaoname+"/" +biaoname  + ".trd";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
            }

       }
       else if(list[0]=="drop")
       {
           QString logName = "D:/MyDataBase/" + user + "/" + kuname +"/" +kuname + ".log";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
       }
       else if(list[0]=="delete")
       {
           int row=list[5].toInt();
           TFile().deleteRecord(user,kuname,biaoname,row);
           QString logName = "D:/MyDataBase/" + user+ "/" + kuname +"/" +biaoname+"/" +biaoname  + ".trd";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
       }
   }
