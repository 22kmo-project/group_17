#include "withdrawal.h"
#include "ui_withdrawal.h"

withdrawal::withdrawal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdrawal)
{
    ui->setupUi(this);
}

withdrawal::~withdrawal()
{
    delete ui;
}
