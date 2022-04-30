#ifndef DFILE_H
#define DFILE_H
#include<qstring.h>
#include<QDir>
#include<QFile>

//对数据库文件进行操作的类

class dfile
{
public:
    dfile();
    //创建数据库文件
    void createDataBase(QString baseName);
    //初始化系统数据库
    void initialDataBase();
private:
    QString baseName;
};

#endif // DFILE_H
