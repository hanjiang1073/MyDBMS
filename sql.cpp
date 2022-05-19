#include "sql.h"
#include <QDateTime>
#include "recordinsert.h"
#include <QString>
SQL::SQL()
{

}
void SQL::GrantU(QString user,QString dba, QString create, QString update, QString dele)//用户授权
{
    QString str="grant ";
    if(dba=="1"){
        str+="dba ";
    }

    if(create=="1"){
        str+="create ";
    }
    if(update=="1"){
        str+="update ";
    }
    if(dele=="1"){
        str+="delete ";
    }
    str=str+"to "+user;
    this->Logic(str,user,"NULL","NUNLL");
}

//修改字段
void SQL::ModifyDesign(QString user, QString databasename, QString tablename,QString prevname, QString str2)
{

    QStringList strs=str2.split("|");
    QString name=strs[0];
    QString type=strs[1];
    QString len=strs[2];
    QString def=strs[3];
    QString mins=strs[4];
    QString maxs=strs[5];
    bool pk=strs[6]=="1"?true:false;
    bool un=strs[7]=="1"?true:false;
    bool non=strs[8]=="1"?true:false;
    QString com=strs[9];
    QString str="alter table "+tablename+" update field "+prevname+" into name:"+name+" type:"+type;
    if(len!="NULL"){
        str+=" length:"+len;
    }
    if(def!="NULL"){
        str+=" default:"+def;
    }
    if(mins!="NULL"||maxs!="NULL"){
        str+=" check in";
        if(mins=="NULL"&&maxs!="NULL"){
            str+=" [MIN,"+maxs+"]";
        }else if(mins!="NULL"&&maxs=="NULL"){
            str+=" ["+mins+",MAX]";
        }
    }
    if(pk==true){
        str+=" primary key";
    }
    if(un==true){
        str+=" unique key";
    }
    if(non==true){
        str+=" not null";
    }
    if(com!="NULL"){
        str+=" comment:"+com;
    }
    this->Logic(str,user,databasename,tablename);
}

//创建表
void SQL::CreateT(QString user,QString databasename ,QString tablename)
{
    QString str="create table "+tablename;//生成语句
      this->Logic(str,user,databasename,tablename);
}

//删除字段
void SQL::deleteField(QString user, QString databasename, QString tablename, QString name){
    QString str="delete fields "+name+" on table "+tablename;
    this->Logic(str,user,databasename,tablename);
}

//删除记录
void SQL::deleteRecord(QString user, QString databasename, QString tablename, int row){
    QString str="delete table "+tablename+" where row= "+ QString::number(row);
    this->Logic(str,user,databasename,tablename);
}

//删除表
void SQL::deleteT(QString user, QString databasename, QString tablename)
{
     QString str="drop table "+tablename;
      this->Logic(str,user,databasename,tablename);
}
//插入记录
void SQL::InsertT(QString user,QString databasename ,QString tablename,QString str2/*表记录语句*/)
{
    QString str="insert into table "+tablename+" "+str2;
    this->Logic(str,user,databasename,tablename);
//    RecordInsert().writeFile(str2,user,databasename,tablename);

}

//创建库
void SQL::CreateD(QString user,QString databasename)
{
    QString tablename;
   QString str="create database "+databasename;
   this->Logic(str,user,databasename,tablename);

}

void SQL::CreateU(QString user,QString databasename)
{
    QString dirname = "D:/MyDataBase/"+user+"/" + databasename;
       QString filename2 =dirname+'/'+databasename +".log";
       QFile logf(filename2);
        QDataStream stream1(&logf);
       QString str="create table "+user+";";


}

//插入字段的sql语句
void SQL::TDesign(QString user,QString databasename, QString tablename, QString name, QString type, QString len, QString def, QString mins, QString maxs, bool pk, bool un, bool non, QString com)//向表插入字段
{   
    QString str="alter table "+tablename+" "+name+" type:"+type;
    if(len!="NULL"){
        str+=" length:"+len;
    }
    if(def!="NULL"){
        str+=" default:"+def;
    }
    if(mins!="NULL"||maxs!="NULL"){
        str+=" check in";
        if(mins=="NULL"&&maxs!="NULL"){
            str+=" [MIN,"+maxs+"]";
        }else if(mins!="NULL"&&maxs=="NULL"){
            str+=" ["+mins+",MAX]";
        }
    }
    if(pk==true){
        str+=" primary key";
    }
    if(un==true){
        str+=" unique key";
    }
    if(non==true){
        str+=" not null";
    }
    if(com!="NULL"){
        str+=" comment:"+com;
    }
    this->Logic(str,user,databasename,tablename);//解析sql语句
    TFile().tabledesign(user,databasename,tablename,name,type,len,def,mins,maxs,pk,un,non,com);


}
//解析SQL语句
void SQL::Logic(QString sql,QString user,QString databasename,QString tablename)
   {
       QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
       QString str1 = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
       QStringList list = sql.split(" ");//将语句分割
       int row=list.size();
     //逐个识别
       if(list[0]=="create")
       {
           if (list[1]=="table") {

                TFile().createTable(user,databasename,list[2]);
                QString logName = "D:/MyDataBase/" + user + "/" + databasename +"/" +tablename+"/"+tablename + ".trd";
                QFile log (logName);
                log.open(QIODevice::Append);
                QDataStream stream (&log);
                  stream<<str1+sql+";";
                  log.close();
              }
           if (list[1]=="database") {

                 DFile().createDataBase(databasename,user);
                 QString filename = "D:/MyDataBase/" + user + "/" + databasename +"/" +databasename + ".log";
                    QFile logf(filename);
                    bool logo = logf.open(QIODevice::ReadWrite);
                     QDataStream stream1(&logf);
                     stream1<<str1+sql+";";
                     logf.close();

              }

           }
       else if(list[0]=="grant")
       {
          QString recName = "D:/MyDataBase/" + user+ "/" + user+ ".rec";
           QFile log (recName);
           QString username;
           log.open(QIODevice::Append);
           QDataStream stream (&log);
            stream<<str1+sql+";";
            log.close();


       }
       else if(list[0]=="insert")
       {
//         QString vaules=list[9];
//         QString name=list[6];
         QString logName = "D:/MyDataBase/" + user + "/" + databasename +"/" +tablename+"/" +tablename+ ".trd";
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
                QString logName = "D:/MyDataBase/" + user+ "/" + databasename +"/" +tablename+"/" +tablename  + ".trd";
                           QFile log (logName);
                           log.open(QIODevice::Append);
                           QDataStream stream (&log);
                           stream<<str1+sql+";";
                           log.close();
            }
           else
            {QString logName = "D:/MyDataBase/" + user+ "/" + databasename +"/" +tablename+"/" +tablename  + ".trd";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
            }

       }
       else if(list[0]=="drop")
       {
           QString logName = "D:/MyDataBase/" + user + "/" + databasename +"/" +databasename + ".log";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
       }
       else if(list[0]=="delete")
       {
           QString logName = "D:/MyDataBase/" + user+ "/" + databasename +"/" +tablename+"/" +tablename  + ".trd";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
       }
   }
