#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myurl.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <QTableWidget>
#include <QtableWidgetItem>


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

public slots:
    void resetInterface();

private slots:
    void on_begin_button_clicked();
    void on_login_button_clicked();
    void loginSlot (QNetworkReply *reply);

    void on_tili_tilanne_table_cellActivated();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString pin_code;
    QString warning1 = "PALVELIN EI VASTAA. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning2 = "VIRHE TIETOKANTA YHTEYDESSÄ. YRITÄ MYÖHEMMIN UUDELLEEN.";
    QString warning3 = "VIRHEELLINEN KÄYTTÄJÄTUNNUS TAI PIN-KOODI! YRITÄ UUDELLEEN. \nYRITYSKERTOJA JÄLJELLÄ: ";
    QTimer *timer;

    QString transaction;
};
#endif // MAINWINDOW_H
