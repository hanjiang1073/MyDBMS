#include "sql.h"
#include <QDateTime>
#include "recordinsert.h"
#include <QString>
SQL::SQL()
{

}
//修改字段
void SQL::ModifyDesign(QString user, QString kuname, QString biaoname,QString prevname, QString str2)
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
    QString str="alter table "+biaoname+" update field "+prevname+" into name:"+name+" type:"+type;
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
    this->Logic(str,user,kuname,biaoname);
}

//创建表
void SQL::CreateT(QString user,QString kuname ,QString biaoname)
{
    QString str="create table "+biaoname;//生成语句
      this->Logic(str,user,kuname,biaoname);
}

//删除字段
void SQL::deleteField(QString user, QString kuname, QString biaoname, QString name){
    QString str="delete fields "+name+" on table "+biaoname;
    this->Logic(str,user,kuname,biaoname);
}

//删除记录
void SQL::deleteRecord(QString user, QString kuname, QString biaoname, int row){
    QString str="delete table "+biaoname+" where row= "+ QString::number(row);
    this->Logic(str,user,kuname,biaoname);
}

//删除表
void SQL::deleteT(QString user, QString kuname, QString biaoname)
{
     QString str="drop table "+biaoname;
      this->Logic(str,user,kuname,biaoname);
}
//插入记录
void SQL::InsertT(QString user,QString kuname ,QString biaoname,QString str2/*表记录语句*/)
{
    QString str="insert into table "+biaoname+" "+str2;
    this->Logic(str,user,kuname,biaoname);
//    RecordInsert().writeFile(str2,user,kuname,biaoname);

}

//创建库
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

//插入字段的sql语句
void SQL::TDesign(QString user,QString kuname, QString biaoname, QString name, QString type, QString len, QString def, QString mins, QString maxs, bool pk, bool un, bool non, QString com)//向表插入字段
{   
    QString str="alter table "+biaoname+" "+name+" type:"+type;
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
    this->Logic(str,user,kuname,biaoname);//解析sql语句
    TFile().tabledesign(user,kuname,biaoname,name,type,len,def,mins,maxs,pk,un,non,com);


}
//解析SQL语句
void SQL::Logic(QString sql,QString user,QString kuname,QString biaoname)
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
//         QString vaules=list[9];
//         QString name=list[6];
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
           QString logName = "D:/MyDataBase/" + user+ "/" + kuname +"/" +biaoname+"/" +biaoname  + ".trd";
           QFile log (logName);
           log.open(QIODevice::Append);
           QDataStream stream (&log);
           stream<<str1+sql+";";
           log.close();
       }
   }
