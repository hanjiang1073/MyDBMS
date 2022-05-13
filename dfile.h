#ifndef DFILE_H
#define DFILE_H
#include <QString>
#include<QDir>
#include<QFile>
#include <QDataStream>
#include <QDebug>
//对数据库文件进行操作的类

class DFile
{
public:
    DFile();
    //创建数据库文件
static int createDataBase(QString baseName ,QString username );
    //初始化系统数据库
static bool initialDataBase();

static bool createUser(QString username, QString secret);
static int userexist(QString username, QString secret);

//获取当前时间
static QString currentTime();

//写入用户记录的粗略日志
static bool addRecord(int type, QString username, QString baseName);

//写入数据库表的粗略日志（添加表 1，操作表 2 ，删除表 3）
static bool addDBRecord(int type, QString username, QString baseName, QString tbname);


private:
    QString baseName;
};

#endif // DFILE_H
