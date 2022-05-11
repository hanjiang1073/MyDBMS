#ifndef BLOGFRAME_H
#define BLOGFRAME_H

#include <QWidget>
#include<QTreeWidgetItem>
#include<QFile>
#include<QDataStream>

namespace Ui {
class blogFrame;
}

class blogFrame : public QWidget
{
    Q_OBJECT

public:
    explicit blogFrame(QWidget *parent = nullptr);
    ~blogFrame();
    void addItem(QTreeWidgetItem* qti);
    void setUser(QString username);

private:
    Ui::blogFrame *ui;
    int checkRFile(QTreeWidgetItem* qti);
    void readBlog(int fileType, QTreeWidgetItem* qti);


private slots:
    void slotDoubleClickItem(QTreeWidgetItem *item, int col);
};

#endif // BLOGFRAME_H
