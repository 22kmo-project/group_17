#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_debit_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_credit_clicked()
{

}

void MainWindow::on_btn_withdrawal_clicked()
{

}


void MainWindow::on_btn_balance_clicked()
{

}


void MainWindow::on_btn_transactions_clicked()
{

}


void MainWindow::on_btn_log_out_clicked()
{

}
