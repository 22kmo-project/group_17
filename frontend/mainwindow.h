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

    void setWebToken(const QByteArray &newWebToken);
    void setUsername(const QString &loggedUser);

public slots:
    void resetInterface();

private slots:
    void on_begin_button_clicked();
    void on_login_button_clicked();
    void loginSlot (QNetworkReply *reply);
    void fetchUserID();
    void fetchUserIDSlot(QNetworkReply *reply);
    void fetchAccounts();
    void fetchAccountSlot(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *userIdManager;
    QNetworkAccessManager *fetchAccManager;
    QNetworkReply *reply;
    QByteArray login_data;
    QByteArray fetch_acc_data;
    QByteArray fetch_user_data;
    QString username;
    QString pin_code;
    QString warning1 = "PALVELIN EI VASTAA. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning2 = "VIRHE TIETOKANTA YHTEYDESSÄ. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning3 = "VIRHEELLINEN KÄYTTÄJÄTUNNUS TAI PIN-KOODI! YRITÄ UUDELLEEN. \nYRITYSKERTOJA JÄLJELLÄ: ";
    QTimer *timer;
};
#endif // MAINWINDOW_H
