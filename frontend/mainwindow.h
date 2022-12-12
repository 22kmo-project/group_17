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

    //Login-toiminnallisuuteen liittyvät tekijät...
    int tries = 3;
    int leftover_tries;
    int connected_accounts;
    QString userid;
    QString account_id_1;
    QString account_id_2;
    QByteArray mytn;
    QString logged_un;
    QString temp_acc_id;

    void setWebToken(const QByteArray &newWebToken);
    void setUsername(const QString &loggedUser);
    //...tekijät

    //tilin valintaan ja tilitietojen hakuun liittyvät...
    QString bank_name, account_holder,account_type, account_number, account_right, balance, fname, lname;
    QString tallennus_at1, tallennus_an1, tallennus_at2, tallennus_an2;
    QString current_account_number;

    void setSaved_AccountType1(const QString &savedAT1);
    void setSaved_AccountNumber1(const QString &savedAN1);
    void setSaved_AccountType2(const QString &savedAT2);
    void setSaved_AccountNumber2(const QString &savedAN2);
    void setAccId(const QString &usedAccId);
    void setAccoundId(const QString &usedAccountId);
    void setAccoundId2(const QString &usedAccountId2);
    //...tekijät

    //tilin nostoon...liittyvät
    double updated_balance;
    int muu_summa, chosen_sum;
    //...tekijät

public slots:
    void resetInterface();
    void returnToMainInterface();
    void moveToEndPage();
    void ShowMoneyInHatch();
private slots:

    //Login-toiminnallisuuteen liittyvät...
    void on_begin_button_clicked();
    void on_login_button_clicked();
    void when_login_button();
    void loginSlot (QNetworkReply *reply);
    void fetchUserID();
    void fetchUserIDSlot(QNetworkReply *reply);
    void fetchHowManyAcc();
    void fetchHowManyAccSlot(QNetworkReply *reply);
    //...tekijät

    //tilin valintaan ja tilitietojen hakuun liittyvät...
    void on_debit_button_clicked();
    void on_credit_button_clicked();
    void fetch_user_full_name();
    void user_full_nameSlot(QNetworkReply *reply);
    void fetch_account_information();
    void account_informationSlot (QNetworkReply *reply);
    void fetch_DataForCompare(QString);
    void CompareDataSlot (QNetworkReply *reply);
    QString CreditOrDebit_testing(QString);
    QString OnlyOneAccount(QString);
    void on_withdraw_button_clicked();
    void on_balance_button_clicked();
    void on_transactions_button_clicked();
    void on_log_out_button_clicked();
    void delay();
    //...tekijät

    //tilin nostoon liittyvät...
    int Substract_withdrawal(int);
    void on_sulje_button_clicked();
    void on_nosto20_button_clicked();
    void on_nosto40_button_clicked();
    void on_nosto60_button_clicked();
    void on_nosto100_button_clicked();
    void on_nosto200_button_clicked();
    void on_muu_summa_button_clicked();
    void on_sulje2_button_clicked();
    void on_nosta_muu_summa_button_clicked();
    void logWithdrawal();
    void logWithdrawalSlot(QNetworkReply *reply);
    void update_balance();
    void update_balanceSlot(QNetworkReply *reply);
    //...tekijät




private:
    Ui::MainWindow *ui;

    //Login-toiminnallisuuteen liittyvät...
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *userIdManager;
    QNetworkAccessManager *fetchAccManager;
    QNetworkReply *reply;
    QByteArray login_data;
    QByteArray fetch_userid_data;
    QByteArray fetch_acc_amount_data;
    QString username;
    QString pin_code;
    QString warning1 = "PALVELIN EI VASTAA. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning2 = "VIRHE TIETOKANTA YHTEYDESSÄ. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning3 = "VIRHEELLINEN KÄYTTÄJÄTUNNUS TAI PIN-KOODI! YRITÄ UUDELLEEN. \nYRITYSKERTOJA JÄLJELLÄ: ";
    QTimer *timer;
    //...tekijät
    //tilin valintaan ja tilitietojen hakuun liittyvät...
    QNetworkAccessManager *account_informationManager;
    QNetworkAccessManager *fetchUserFullNameManager;
    QNetworkAccessManager *CompareDataManager;
    QByteArray response_account_information;
    QByteArray response_user_fullname;
    QByteArray response_CompareData;
    QTimer *timer2;
    QString test_at1, test_an1;
    QString debit ="Debit";
    QString credit = "Credit";
    //...tekijät

    //tilin nostoon liittyvät...
    QString varoitus1 = "Syötettyä summaa ei voida nostaa! Kokeile pienempää summaa";
    QString varoitus2 = "Ei seteleitä saatavilla, syötä muu summa";
    QTimer *timer3;
    QTimer *timer4;
    QNetworkAccessManager *withdrawal_logManager;
    QByteArray withdrawal_log_data;
    QString transaction_type = "NOSTO";
    QNetworkAccessManager *update_balanceManager;
    QByteArray update_balance_data;
    //...tekijät
};
#endif // MAINWINDOW_H
