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
    QString kuname;
    QString biaoname;
    QTreeWidgetItem *kuItem=NULL;
    QTreeWidgetItem *biaoItem=NULL;
    void initTableWidget();
    void writeFile(QString str);
    bool checkdigit(std::string svalue);
private:
    Ui::RecordInsert *ui;
private slots:
    void on_button_confirm();
    void on_button_reset();
};

#endif // RECORDINSERT_H
