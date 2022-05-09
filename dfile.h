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
private:
    QString baseName;
};

#endif // DFILE_H
