#include "blogframe.h"
#include "ui_blogframe.h"

blogFrame::blogFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::blogFrame)
{

    ui->setupUi(this);
    connect(ui->treewid,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slotDoubleClickItem(QTreeWidgetItem *, int)));

}

blogFrame::~blogFrame()
{
    delete ui;
}


//添加一个项目
void blogFrame::addItem(QTreeWidgetItem *qti)
{
    QTreeWidgetItem * temp =ui->treewid->topLevelItem(0);
    temp->addChild(qti);
}


//设置用户
void blogFrame::setUser(QString username)
{
    QTreeWidgetItem * user = new QTreeWidgetItem();
    user->setText(0,username);
    ui->treewid->addTopLevelItem(user);

}


//检测是用户一级还是库一级还是表一级
int blogFrame::checkRFile(QTreeWidgetItem *qti)
{
    int filetype = 1;
    while(qti->parent()!=NULL){
        filetype++;
        qti = qti->parent();
    }
    return filetype;
}


//获取日志
void blogFrame::readBlog(int fileType, QTreeWidgetItem *qti)
{
    ui->textBrowser->clear();
    QString fileName = "D:/MyDataBase";
    QString file = "/"+qti->text(0);
    for (int i =0;i<fileType ; i++) {
       file = "/"+qti->text(0) + file;
       qti = qti->parent();
    }
    file = fileName + file;
    switch (fileType) {
    case 1:
        file = file + ".rec";
        break;
    case 2:
        file = file + ".log";
        break;
    case 3:
        file = file + ".trd";
        break;
    }

    qDebug()<<file;
    QFile qf (file);
    qf.open(QIODevice::ReadOnly);
    QDataStream stream(&qf);
    QString temp;
    while (!stream.atEnd()) {
        stream >> temp;
        ui->textBrowser->append(temp+"\n");

    }
}


//双击显示日志
void blogFrame::slotDoubleClickItem(QTreeWidgetItem *item, int col)
{
   int type = this->checkRFile(item);
   this->readBlog(type, item);
   qDebug()<< type;
}
