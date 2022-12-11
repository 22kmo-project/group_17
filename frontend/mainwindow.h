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

    void setWebToken(const QByteArray &newWebToken);
    void setUsername(const QString &loggedUser);
    //...tekijät

public slots:
    void resetInterface();

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
};
#endif // MAINWINDOW_H
