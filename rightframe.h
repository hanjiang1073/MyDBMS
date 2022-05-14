#ifndef RIGHTFRAME_H
#define RIGHTFRAME_H

#include <QWidget>
#include <QFile>
#include <QDataStream>
#include <QDebug>
namespace Ui {
class RightFrame;
}

class RightFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RightFrame(QWidget *parent = nullptr);
    ~RightFrame();
    void initWidget();
    QString user;//当前管理员用户名
    bool dbaright=true;//记录当前管理员权限是否改变用于信号传递
    bool createright=true;
    bool updateright=true;
    bool deleright=true;
    QStringList pws;//记录各用户密码
signals:
    void change(bool,bool,bool,bool);
private:
    Ui::RightFrame *ui;

private slots:
    void confirm();
    void reset();
};

#endif // RIGHTFRAME_H
