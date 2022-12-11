#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //Asetetaan aloitussivu
    ui->stackedWidget->setCurrentIndex(0);
    //Luodaan timeri jonka avulla hoidetaan aikakatkaisut
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(resetInterface()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWebToken(const QByteArray &newWebToken)
{
    mytn = newWebToken;
}

void MainWindow::setUsername(const QString &loggedUser)
{
    logged_un = loggedUser;
}

//Aikakatkaisuun liittyvä, käyttöliittymän resetointi
void MainWindow::resetInterface()
{
    qDebug()<<"Timer finished.";
    ui->stackedWidget->setCurrentIndex(0);
    tries = 3;
    ui->warning_label->clear();
}

// Aloitusnäytön nappula jolla siirrytään Sisäänkirjautumisnäyttöön.
void MainWindow::on_begin_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    timer->start(30000);
    qDebug()<<"Timer Started.";
}

// Sisäänkirjautumisnapin toiminnot
void MainWindow::on_login_button_clicked()
{
    timer->stop();
    leftover_tries = tries - 1;
    tries = leftover_tries;

    //If-lauseella tarkistetaan yrityskerrat
    if(tries != 0) {
        username=ui->username_input_edit->text();
        pin_code=ui->pin_input_edit->text();
        setUsername(username);
        qDebug()<<logged_un;

        QJsonObject jsonObj;
        jsonObj.insert("username",username);
        jsonObj.insert("pin_code",pin_code);

        QString site_url=MyUrl::getBaseUrl()+"/login";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        loginManager = new QNetworkAccessManager(this);
        connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

        reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

    }
    // Jos yrityskerrat nollissa, asetetaan kortille lukitus
    else {
        //ui->username_input_edit->clear();
        ui->pin_input_edit->clear();
        ui->stackedWidget->setCurrentIndex(2);
        timer->start(10000);
    }
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    login_data=reply->readAll();
    qDebug()<<login_data;

    int test=QString::compare(login_data,"false");
    qDebug()<<test;
    ui->warning_label->setStyleSheet("color: red;");

    if(login_data.length()==0){
        ui->warning_label->setText(warning1);
    }
    else {
        if(QString::compare(login_data,"-4078")==0){
            ui->warning_label->setText(warning2);
        }
        else {
            if(test==0){
                QString leftover_tries_string = QString::number(leftover_tries);
                //ui->username_input_edit->clear();
                ui->pin_input_edit->clear();
                ui->warning_label->setText(warning3 + leftover_tries_string);
                timer->start(30000);
            }
            // Jos kirjautumistunnukset kunnossa, siirrytään tilinvalintaan.
            else {
                qDebug()<<logged_un;

                timer->stop();
                ui->pin_input_edit->clear();

                // WEBTOKEN LUONTI
                setWebToken("Bearer "+login_data);

                fetchUserID();
                }
            }
        }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::fetchUserID()
{
    qDebug()<<"onko fetch "+logged_un;
    QString site_url=MyUrl::getBaseUrl()+"/login/"+logged_un;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    userIdManager = new QNetworkAccessManager(this);

    connect(userIdManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(fetchUserIDSlot(QNetworkReply*)));

    reply = userIdManager->get(request);
}

void MainWindow::fetchUserIDSlot(QNetworkReply *reply)
{
    qDebug()<<"onko fetchslot "+logged_un;
    fetch_user_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(fetch_user_data);
    QJsonObject json_obj = json_doc.object();
    userid = QString::number(json_obj["id_user"].toInt());
    qDebug()<<"Asiakkaan id on: " +userid;

    fetchAccounts();

    reply->deleteLater();
    userIdManager->deleteLater();
}

void MainWindow::fetchAccounts()
{
    qDebug()<<"Asiakkaan arvo edelleen:" + userid;
    QString site_url=MyUrl::getBaseUrl()+"/account_right";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    fetchAccManager = new QNetworkAccessManager(this);

    connect(fetchAccManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(fetchAccountSlot(QNetworkReply*)));

    reply = fetchAccManager->get(request);
}

void MainWindow::fetchAccountSlot(QNetworkReply *reply)
{
     fetch_acc_data=reply->readAll();
     qDebug()<<"DATA : "+fetch_acc_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(fetch_acc_data);
     QJsonArray json_array = json_doc.array();
     QString total_userids;
     foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        total_userids+= QString::number(json_obj["id_user"].toInt())+ " , ";
     }

     connected_accounts = total_userids.count(userid);
     qDebug()<< total_userids.count(userid);

     switch(connected_accounts) {
         case 1:
             ui->stackedWidget->setCurrentIndex(4);
         case 2:
             ui->stackedWidget->setCurrentIndex(3);
     }

     reply->deleteLater();
     fetchAccManager->deleteLater();
}
