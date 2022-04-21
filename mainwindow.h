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
private:
    Ui::MainWindow *ui;
    LoginFrame *lf;//登入窗口
private slots:
    void on_actionExit_triggered();
};
#endif // MAINWINDOW_H
