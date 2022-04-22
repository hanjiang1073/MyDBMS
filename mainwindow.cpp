#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    createMenu();
    createTreeWidget();
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
    connect(ui->actionxjk,&QAction::triggered,this,&MainWindow::on_actionXjk_triggered);
    connect(ui->actionxjb,&QAction::triggered,this,&MainWindow::on_actionXjb_triggered);
    connect(ui->actiondkk,&QAction::triggered,this,&MainWindow::on_actionDkk_triggered);
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

void MainWindow::createTreeWidget(){
    //Item点击事件的连接
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slotDoubleClickItem(QTreeWidgetItem *, int)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(slotClickItem(QTreeWidgetItem*,int)));
    //这里之后写该用户已有数据库的自动载入


}

//新建库槽函数
void MainWindow::on_actionXjk_triggered(){
    QTreeWidgetItem *Ku=new QTreeWidgetItem(ui->treeWidget);
    QIcon icon;
    icon.addPixmap(QPixmap(":/pic/Ku.png"), QIcon::Selected);
    Ku->setIcon(0,icon);
    Ku->setText(0,QString::fromLocal8Bit("请输入名称"));

}
//新建表槽函数
void MainWindow::on_actionXjb_triggered(){
    if(kuItem!=NULL){
        QTreeWidgetItem *biao=new QTreeWidgetItem();
        kuItem->addChild(biao);
        QIcon icon;
        icon.addPixmap(QPixmap(":/pic/biao.png"), QIcon::Selected);
        biao->setIcon(0,icon);
        biao->setText(0,QString::fromLocal8Bit("请输入名称"));
    }else{
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请先选择库!"));
    }
}
//TreeWidgetItem双击改名
void MainWindow::slotDoubleClickItem(QTreeWidgetItem *item, int col) {
    doubleClickItem = nullptr;
    if (col == 0) {
        doubleClickItem = item;
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(QStringLiteral("请输入名称"));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(slotFinishEdit()));
        ui->treeWidget->setItemWidget(doubleClickItem, 0, lineEdit);
    }
}

void MainWindow::slotFinishEdit(){
    if (doubleClickItem != nullptr) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(ui->treeWidget->itemWidget(doubleClickItem, 0));
        if (!edit) {
            return;
        }
        QString text = edit->text();
        ui->treeWidget->removeItemWidget(doubleClickItem, 0);
        if(text==""){
            QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入名称"));
        }else{
            //这里应该将名称记录到对应数据字典中(在数据字典中无同名数据库的情况下，这个同名的检索时间充裕做)
            doubleClickItem->setText(0, text);
            QMessageBox::StandardButton button;
            button = QMessageBox::question(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("名称无法修改，确定此名？") ,QMessageBox::Yes | QMessageBox::No);
        }
    }
}
//单击（选中）槽函数
void MainWindow::slotClickItem(QTreeWidgetItem *item,int col){
    QTreeWidgetItem *p=NULL;
    p=item->parent();
    if(p!=NULL){
        biaoItem=item;
        //如果说单击的这个item不是根节点即不是库，是表那么就显示其设计界面
    }else{
        kuItem=item;
    }
}

//展开库
void MainWindow::on_actionDkk_triggered(){
    if(kuItem!=NULL){
        kuItem->setExpanded(1);
    }
}
