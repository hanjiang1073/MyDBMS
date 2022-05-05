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

    if(DFile().initialDataBase()){

        qDebug() << "here"<<1;
    }
    connect(lf,SIGNAL(login(QString)),this,SLOT(initall(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//菜单栏创建(与槽函数连接)其他功能连接也在这进行
//具体控件名字见.ui文件
void MainWindow::createMenu(){
    connect(ui->actionquit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    connect(ui->actionxjk,&QAction::triggered,this,&MainWindow::on_actionXjk_triggered);    //新建库
    connect(ui->actionxjb,&QAction::triggered,this,&MainWindow::on_actionXjb_triggered);    //新建表
    connect(ui->actiondkk,&QAction::triggered,this,&MainWindow::on_actionDkk_triggered);    //打开库
    connect(ui->actioncrd,&QAction::triggered,this,&MainWindow::on_actionCrd_triggered);    //插入字段
    connect(ui->actioncrj,&QAction::triggered,this,&MainWindow::on_actionCrj_triggered);    //插入记录

}

//根据当前用户初始化所有信息
void MainWindow::initall(QString name){
    this->user=name;
    //TODO根据user名加载出这个用户已经存在的库、表、记录

    this->show();
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
    button = QMessageBox::question(this, QStringLiteral("提示"),QStringLiteral("是否退出程序") ,QMessageBox::Yes | QMessageBox::No);
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
}

//新建库槽函数
void MainWindow::on_actionXjk_triggered(){
    QTreeWidgetItem *Ku=new QTreeWidgetItem(ui->treeWidget);
    QIcon icon;
    icon.addPixmap(QPixmap(":/pic/Ku.png"), QIcon::Selected);
    Ku->setIcon(0,icon);

    Ku->setText(0,QStringLiteral("请输入名称"));

}
//新建表槽函数
void MainWindow::on_actionXjb_triggered(){
    if(kuItem!=NULL){
        QTreeWidgetItem *biao=new QTreeWidgetItem();
        kuItem->addChild(biao);
        QIcon icon;
        icon.addPixmap(QPixmap(":/pic/biao.png"), QIcon::Selected);
        biao->setIcon(0,icon);
        biao->setText(0,QStringLiteral("请输入名称"));
    }else{
        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("请先选择库!"));
    }

}

//插入字段槽函数
void MainWindow::on_actionCrd_triggered(){
    if(this->biaoItem!=NULL){
        td=new TableDesign();
        td->biaoItem=this->biaoItem;//传递选中的表指针以便存值
        td->kuname=this->kuname;
        td->biaoname=this->biaoname;
        td->user=this->user;
        td->show();
        showTableWidget();

    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}

//插入记录
void MainWindow::on_actionCrj_triggered(){
    if(this->biaoItem!=NULL){
        ri=new RecordInsert(); 
        ri->biaoItem=this->biaoItem;
        ri->user=this->user;
        ri->initTableWidget();
        ri->show();
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}

//TreeWidgetItem(库表)双击改名
void MainWindow::slotDoubleClickItem(QTreeWidgetItem *item, int col) {
    doubleClickItem = nullptr;
    if(hasht[item]==1){
        return ;
    }
    if (col == 0) {
        doubleClickItem = item;
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(QStringLiteral("请输入名称"));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(slotFinishEdit()));
        ui->treeWidget->setItemWidget(doubleClickItem, 0, lineEdit);
    }
}

//(库表)改名结束
void MainWindow::slotFinishEdit(){
    if (doubleClickItem != nullptr) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(ui->treeWidget->itemWidget(doubleClickItem, 0));
        if (!edit) {
            return;
        }
        QString text = edit->text();
        ui->treeWidget->removeItemWidget(doubleClickItem, 0);
        if(text==""){
            QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请输入名称"));

        }else{

            doubleClickItem->setText(0,text);
            if(doubleClickItem==kuItem)
            {
                kuname=text;
                 DFile::createDataBase(text,this->user);
            }
            if(doubleClickItem==biaoItem)
            {
                 TFile::createTable(this->user,kuname,text);
            }
            QMessageBox::StandardButton button;
            button = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("名称无法修改，确定此名？") ,QMessageBox::Yes | QMessageBox::No);
              //字段设计窗口//TODO这里应该将名称记录到对应数据字典中(在数据字典中无同名的情况下，如果同名则提示失败)

        }
        hasht[doubleClickItem]=1;
    }
}
//单击（选中）槽函数
void MainWindow::slotClickItem(QTreeWidgetItem *item,int col){
    QTreeWidgetItem *p=NULL;
    p=item->parent();
    if(p!=NULL){
        biaoItem=item;
       kuname=item->parent()->text(0);
       biaoname=item->text(0);
      // biaoname=biaoItem->text(0);
       kuItem=NULL;
        //如果说单击的这个item不是根节点即不是库，是表那么就显示其设计界面
        showTableWidget();
    }else{
        kuItem=item;
        // kuname=kuItem->text(col);
         biaoItem=NULL;
    }
}

//展开库
void MainWindow::on_actionDkk_triggered(){
    if(kuItem!=NULL){
        kuItem->setExpanded(1);
    }
}

//显示图表
void MainWindow::showTableWidget(){
    //先清空
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //创建表头
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("字段名")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("字段类型")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("长度")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("默认值")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("最小值")));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem(QStringLiteral("最大值")));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem(QStringLiteral("主键")));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem(QStringLiteral("唯一键")));
    ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem(QStringLiteral("非空")));
    ui->tableWidget->setHorizontalHeaderItem(9,new QTableWidgetItem(QStringLiteral("注释")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//TODO下面读取字段信息



//    int RowCont;
//    RowCont=ui->tableWidget->rowCount();
//qDebug()<<RowCont;
//    ui->tableWidget->setRowCount(RowCont+1);//增加一行
//qDebug()<<RowCont;
//    ui->tableWidget->setItem(0,0,new QTableWidgetItem("你好"));//测试
//    ui->tableWidget->setItem(1,0,new QTableWidgetItem("你好"));
//qDebug()<<"单元格 你好";

    QString dirname = "D:/MyDataBase/"+ user+'/' + kuname+'/'+biaoname;
    QString filename_tdf = dirname + '/' + biaoname + ".tdf";
    QFile tdf(filename_tdf);
    tdf.seek(0);
    if(tdf.open(QIODevice::ReadWrite))
    {
qDebug()<<"文件打开成功";
    }
    QDataStream stream (&tdf);

    QString str;
    QStringList strlist;

if(stream.atEnd())
qDebug()<<"stream到尾巴了";

    //将值分解后写入单元格
    while(!stream.atEnd()){
qDebug()<<"进入循环了！";
        int RowCont;
        RowCont=ui->tableWidget->rowCount();
//qDebug()<<"RowCont:"<<RowCont;
        ui->tableWidget->setRowCount(RowCont+1);//增加一行
        stream>>str;

        strlist=str.split("|");
        for(int j=0;j<=9;j++)
        {
            if(j==6||j==7||j==8)
            {
                if(strlist[j]=="1")
                {
                    QTableWidgetItem *citem=new QTableWidgetItem();
                    QIcon icon;
                    icon.addPixmap(QPixmap(":/pic/choose.jpg"));
                    citem->setTextAlignment(Qt::AlignCenter);
                    citem->setIcon(icon);
                    ui->tableWidget->setItem(0,j,citem);
                }

            }else
            {
                ui->tableWidget->setItem(0,j,new QTableWidgetItem(strlist[j]));
            }

        }
    }
    tdf.close();

}
