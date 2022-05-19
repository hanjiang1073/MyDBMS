#ifndef RECORDINSERT_H
#define RECORDINSERT_H

#include <QWidget>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFile>
namespace Ui {
class RecordInsert;
}

class RecordInsert : public QWidget
{
    Q_OBJECT

public:
    explicit RecordInsert(QWidget *parent = nullptr);
    ~RecordInsert();
    QString user;//当前用户
    QString databasename;
    QString tablename;
    QTreeWidgetItem *databaseItem=NULL;
    QTreeWidgetItem *tableItem=NULL;
    std::vector<int>pks;//记录主键的字段
    void initTableWidget();//初始化界面
    void writeFile(QString str);//写入文件
    bool checkdigit(std::string svalue);//判断是否是数字
    bool checkUnique(QString value,int row);//判断是否唯一
    void changeLabel(QString text);
private:
    Ui::RecordInsert *ui;
private slots:
    void on_button_confirm();
    void on_button_reset();
};

#endif // RECORDINSERT_H
