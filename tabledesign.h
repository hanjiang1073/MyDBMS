#ifndef TABLEDESIGN_H
#define TABLEDESIGN_H

#include <QWidget>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QDebug>
namespace Ui {
class TableDesign;
}

class TableDesign : public QWidget
{
    Q_OBJECT

public:
    explicit TableDesign(QWidget *parent = nullptr);
    ~TableDesign();
    void connection();
    QString user;//当前用户
    QTreeWidgetItem *kuItem=NULL;
    QTreeWidgetItem *biaoItem=NULL;
private:
    Ui::TableDesign *ui;

private slots:
    void on_comboBox_CIC(const QString &arg);//字段类型选择
    void on_checkBox_pkc();//主键选择
    void on_button_confirm();//确认按钮
    void on_button_reset();//重置按钮
};

#endif // TABLEDESIGN_H
