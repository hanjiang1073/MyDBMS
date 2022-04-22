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
private:
    Ui::MainWindow *ui;
    LoginFrame *lf;//登入窗口
    QTreeWidgetItem *doubleClickItem=NULL;
    QTreeWidgetItem *kuItem=NULL;
    QTreeWidgetItem *biaoItem=NULL;
private slots:
    void on_actionExit_triggered();
    void on_actionXjk_triggered();
    void on_actionXjb_triggered();
    void on_actionDkk_triggered();
    void slotClickItem(QTreeWidgetItem *item,int col);//单击事件
    void slotDoubleClickItem(QTreeWidgetItem *item, int col);//双击改名
    void slotFinishEdit();//配合双击改名并存储的
};
#endif // MAINWINDOW_H
