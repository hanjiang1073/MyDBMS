#ifndef QUERYFRAME_H
#define QUERYFRAME_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class QueryFrame;
}

class QueryFrame : public QWidget
{
    Q_OBJECT

public:
    explicit QueryFrame(QWidget *parent = nullptr);
    ~QueryFrame();
    void showWidget();
    QString user;//当前用户
    QString kuname;
    QString biaoname;
    QTreeWidgetItem *kuItem=NULL;
    QTreeWidgetItem *biaoItem=NULL;
signals:
    void submit(QString);
private:
    Ui::QueryFrame *ui;

private slots:
    void confirm();
};

#endif // QUERYFRAME_H
