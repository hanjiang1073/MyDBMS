#include "rightframe.h"
#include "ui_rightframe.h"

RightFrame::RightFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightFrame)
{
    ui->setupUi(this);
}

RightFrame::~RightFrame()
{
    delete ui;
}

//初始化权限表
void RightFrame::initWidget(){
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("用户名")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("管理员")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("创建权限")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("修改权限")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("删除权限")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    //载入用户名及相关权限
    QString path="D:/MyDataBase/ID.nf";
    QFile idf(path);
    idf.seek(0);
    if(idf.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream stream (&idf);
    QString str;
    while(!stream.atEnd()){
        int row=ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);
        for(int i=0;i<6;i++){
            stream>>str;
            if(i==1){
                pws.push_back(str);
                continue;
            }
            else if(i==0){
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(str));
            }else{
                //对于权限，设置comboBox
                 QTableWidgetItem *itemcheck = new QTableWidgetItem();
                 if(str=="0"){
                      itemcheck->setCheckState(Qt::Unchecked);
                 }else{
                     itemcheck->setCheckState(Qt::Checked);
                 }
                ui->tableWidget->setItem(row,i-1,itemcheck);
            }
        }
    }
}

//确认按钮
void RightFrame::confirm(){
    QString path="D:/MyDataBase/ID.nf";
    QFile idf(path);
    idf.open(QFile::WriteOnly|QIODevice::Truncate);//先清空
    idf.open(QFile::Append);
    idf.seek(0);//再写入
    QDataStream stream (&idf);
    int flag=0;
    int rows=ui->tableWidget->rowCount();
    for(int i=0;i<rows;i++){
        if(flag==1){
            flag=0;
        }
        for(int j=0;j<6;j++){
            if(j==1){
                stream<<pws[i];
            }else{
                QTableWidgetItem*item;
                if(j==0){
                    item=ui->tableWidget->item(i,0);
                    QString text=item->text();
                    stream<<text;
                    //检查当前行是否是管理员的行
                    if(text==user){
                        flag=1;
                    }
                }else{
                    item=ui->tableWidget->item(i,j-1);
                    int check;
                    check=item->checkState()?1:0;
                    stream<<QString::number(check);
                    if(flag==1){
                        //重新记录当前管理员权限
                        switch (j) {
                        case 2:
                            dbaright=check;
                            break;
                        case 3:
                            createright=check;
                            break;
                        case 4:
                            updateright=check;
                            break;
                        case 5:
                            deleright=check;
                            break;
                        default:
                            break;
                        }
                    }

                }
            }
        }
    }
    idf.close();
    emit(change(dbaright,createright,updateright,deleright));
    this->close();
}

//重置按钮
void RightFrame::reset(){
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    initWidget();
}
