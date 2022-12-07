#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_debit_clicked();

    void on_btn_credit_clicked();

    void on_btn_withdrawal_clicked();

    void on_btn_balance_clicked();

    void on_btn_transactions_clicked();

    void on_btn_log_out_clicked();

    void on_begin_button_clicked();

    void on_login_button_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
