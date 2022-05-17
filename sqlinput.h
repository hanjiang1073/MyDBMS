#ifndef SQLINPUT_H
#define SQLINPUT_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "sql.h"
#include "tfile.h"
#include <QMap>
namespace Ui {
class SqlInput;
}

class SqlInput : public QWidget
{
    Q_OBJECT

public:
    explicit SqlInput(QWidget *parent = nullptr);
    ~SqlInput();
    void sqlTran(QString str);//sql语句解析
    QString user;//用户名
    QString databasename;//库名
    QString tablename;//表名
signals:
    void query(QString);
private:
    Ui::SqlInput *ui;
private slots:
    void inputFile();//导入文件
    void confirm();//确定按钮
    void reset();//重置按钮
};

#endif // SQLINPUT_H
