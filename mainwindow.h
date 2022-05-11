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
    void createTreeWidget();
    void showTableWidget();

private:
    Ui::MainWindow *ui;
    QString user;//当前用户
    QString kuname;
    QString biaoname;
    LoginFrame *lf;//登入窗口
    TableDesign *td;//字段设计窗口
    RecordInsert *ri;//记录窗口
    QMap<QTreeWidgetItem*,int>hasht;//用于记录表/库是否已经改名
     QMap<QTreeWidgetItem*,QString>hasht1;//用于存储已经生成的表/库
    QTreeWidgetItem *doubleClickItem=NULL;
    QTreeWidgetItem *kuItem=NULL;//指针指向选中的库
    QTreeWidgetItem *biaoItem=NULL;//指针指向选中的表，kuItem与biaoItem两者只能有一个不为空，因为只能选择一个

private slots:
    void on_actionExit_triggered();
    void on_actionXjk_triggered();
    void on_actionXjb_triggered();
    void on_actionDkk_triggered();
    void on_actionCrd_triggered();
    void on_actionCrj_triggered();
    void on_actionTjc_triggered();
    void on_actionrizhi_triggered();
    void forTjc(QString values);//条件查询接收子窗口信号的函数
    void slotClickItem(QTreeWidgetItem *item,int col);//单击事件
    void slotDoubleClickItem(QTreeWidgetItem *item, int col);//双击改名
    void slotFinishEdit();//配合双击改名并存储的
    void initall(QString name);
    void showRecord();
};
#endif // MAINWINDOW_H
