#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myurl.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int tries = 3;
    int leftover_tries;
    int connected_accounts;
    QString userid;
    QByteArray mytn;
    QString logged_un;
    QString bank_name, account_holder,account_type, account_number, account_right, balance, fname, lname;
    QString tallennus_at1, tallennus_an1, tallennus_at2, tallennus_an2;
    QString current_account_number;

    void setWebToken(const QByteArray &newWebToken);
    void setUsername(const QString &loggedUser);

    void setSaved_AccountType1(const QString &savedAT1);
    void setSaved_AccountNumber1(const QString &savedAN1);
    void setSaved_AccountType2(const QString &savedAT2);
    void setSaved_AccountNumber2(const QString &savedAN2);

public slots:
    void resetInterface();
    void returnToMainInterface();

private slots:
    void on_begin_button_clicked();
    void on_login_button_clicked();
    void loginSlot (QNetworkReply *reply);
    void fetchUserID();
    void fetchUserIDSlot(QNetworkReply *reply);
    void fetchAccounts();
    void fetchAccountSlot(QNetworkReply *reply);


    void on_debit_button_clicked();
    void on_credit_button_clicked();
    void fetch_user_full_name();
    void user_full_nameSlot(QNetworkReply *reply);
    void fetch_account_information();
    void account_informationSlot (QNetworkReply *reply);
    void fetch_DataForCompare(QString);
    void CompareDataSlot (QNetworkReply *reply);
    QString CreditOrDebit_testing(QString);
    void on_withdraw_button_clicked();
    void on_balance_button_clicked();
    void on_transactions_button_clicked();
    void on_log_out_button_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *userIdManager;
    QNetworkAccessManager *fetchAccManager;
    QNetworkAccessManager *account_informationManager;
    QNetworkAccessManager *fetchUserFullNameManager;
    QNetworkAccessManager *CompareDataManager;
    QNetworkReply *reply;
    QByteArray login_data;
    QByteArray fetch_acc_data;
    QByteArray fetch_user_data;
    QByteArray response_account_information;
    QByteArray response_user_fullname;
    QByteArray response_CompareData;
    QString username;
    QString pin_code;
    QString warning1 = "PALVELIN EI VASTAA. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning2 = "VIRHE TIETOKANTA YHTEYDESSÄ. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning3 = "VIRHEELLINEN KÄYTTÄJÄTUNNUS TAI PIN-KOODI! YRITÄ UUDELLEEN. \nYRITYSKERTOJA JÄLJELLÄ: ";
    QTimer *timer;
    QTimer *timer2;
    QString test_at1, test_at2, test_an1, test_an2,debit, credit;
};
#endif // MAINWINDOW_H
