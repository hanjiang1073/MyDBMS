#include "sqlinput.h"
#include "ui_sqlinput.h"

SqlInput::SqlInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlInput)
{
    ui->setupUi(this);
}

SqlInput::~SqlInput()
{
    delete ui;
}
