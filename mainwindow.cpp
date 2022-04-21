#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    createMenu();
    lf=new LoginFrame();
    lf->show();
    connect(lf,SIGNAL(login()),this,SLOT(show()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//菜单栏创建(与槽函数连接)其他功能连接也在这进行
//具体控件名字见.ui文件
void MainWindow::createMenu(){
    connect(ui->actionquit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
}


//退出按钮槽函数
void MainWindow::on_actionExit_triggered()
{
    this->close();
}
//有条件退出
void MainWindow::closeEvent(QCloseEvent* event)
{
    /*
    event->accept();//接受退出
    event->ignore();//不接受退出
    */
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("是否退出程序") ,QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes)
    {
        event->accept();//接受退出
    }
    else
    {
        event->ignore();//不接受退出
    }
}
