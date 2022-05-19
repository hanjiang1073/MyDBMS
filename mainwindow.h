#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QCloseEvent>
#include <QThread>
#include "loginframe.h"
#include <QIcon>
#include <QLineEdit>
#include <QDebug>
#include "tabledesign.h"
#include <QMap>
#include "recordinsert.h"
#include<QTableWidgetItem>
#include "queryframe.h"
#include"blogframe.h"
#include"sql.h"
#include "rightframe.h"
#include "QFileDialog"
#include "sqlinput.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);
    void createMenu();
    void createWidget();
    void showTableWidget();

private:
    Ui::MainWindow *ui;
    QString user;//当前用户
    bool dbaright;//标志当前是否为dba
    bool createright;//标志是否有创建权限
    bool updateright;//标志是否有修改权限
    bool deleright;//标志是否有删除权限
    QString databasename;
    QString tablename;
    LoginFrame *lf;//登入窗口
    TableDesign *td;//字段设计窗口
    RecordInsert *ri;//记录窗口
    QMap<QTreeWidgetItem*,int>hasht;//用于记录表/库是否已经改名
     QMap<QTreeWidgetItem*,QString>hasht1;//用于存储已经生成的表/库
    QTreeWidgetItem *doubleClickItem=NULL;
    QTreeWidgetItem *databaseItem=NULL;//指针指向选中的库
    QTreeWidgetItem *tableItem=NULL;//指针指向选中的表，databaseItem与tableItem两者只能有一个不为空，因为只能选择一个
    int recordRow;  //选中记录行数
    int tableRow=-1;   //选中字段行数
    bool recordTable=false;//判断当前界面是否是表界面而不是字段界面
private slots:
    void actionExit();//退出
    void createDatabase();//创建库
    void createTable();//创建表
    void openDatabase();//打开库
    void insertField();//插入字段
    void insertRecord();//插入记录
    void queryRecord();//查询记录
    void systemLog();//系统日志
    void deleteField();//删除字段
    void updateField();//修改字段
    void updateRecord();//修改记录
    void deleteRecord();//删除记录
    void controlRight();//权限管理
    void userInfo();//用户信息
    void actionSql();//sql命令
    void actionReload();//重载库表界面
    void deleteDatabase();//删除数据库
    void deleteTable();//删除表
    void forTjc(QString values);//条件查询接收子窗口信号的函数
    void slotClickItem(QTreeWidgetItem *item,int col);//单击选择库、表
    void slotDoubleClickItem(QTreeWidgetItem *item, int col);//双击改名
    void slotFinishEdit();//配合双击改名并存储的
    void initall(QString name,QString dba,QString create,QString update,QString dele);//用户登入初始化库表
    void showRecord();//打开表（记录）
    void slotClickTableItem(int row,int column);//双击选中记录
    void changeRight(bool dba,bool create,bool update,bool dele);
};
#endif // MAINWINDOW_H
