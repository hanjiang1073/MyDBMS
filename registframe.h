#ifndef REGISTFRAME_H
#define REGISTFRAME_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class RegistFrame;
}

class RegistFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RegistFrame(QWidget *parent = nullptr);
    ~RegistFrame();
signals:
    void confirm();
private:
    Ui::RegistFrame *ui;
public slots:
    void btn_confirm_clicked();
};

#endif // REGISTFRAME_H
