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

//Asetaan webtokeni siten, että käytettävissä aina tarvittaessa
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

//Sisäänkirjautumisnapin toiminnot
void MainWindow::on_login_button_clicked()
{
    when_login_button();
}

//Funktio joka kutsutaan login-painikkeella
void MainWindow::when_login_button()
{
    timer->stop();
    //Joka klikkausyrityksellä vähennetään yrityskertoja
    leftover_tries = tries - 1;
    tries = leftover_tries;

    //If-lauseella tarkistetaan yrityskerrat
    if(tries != 0) {
        username=ui->username_input_edit->text();
        pin_code=ui->pin_input_edit->text();

        //Asetetaan talteen username
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

    //Jos palvelinongelmia
    if(login_data.length()==0){
        ui->warning_label->setText(warning1);
    }
    //Jos tietokantaongelmia
    else {
        if(QString::compare(login_data,"-4078")==0){
            ui->warning_label->setText(warning2);
        }
        else {
            //Jos virheellinen tietojen syöttö
            if(test==0){
                QString leftover_tries_string = QString::number(leftover_tries);
                //ui->username_input_edit->clear();
                ui->pin_input_edit->clear();
                ui->warning_label->setText(warning3 + leftover_tries_string);
                timer->start(30000);
            }
            // Jos kirjautumistunnukset kunnossa, siirrytään tilinvalintaan
            else {
                qDebug()<<logged_un;

                timer->stop();
                ui->pin_input_edit->clear();

                // WEBTOKEN LUONTI
                setWebToken("Bearer "+login_data);

                // Lähdetään tarkistamaan onko useampi kuin yksi tili kortissa
                fetchUserID();
                }
            }
        }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::fetchUserID()
{
    //Lähetään hakemaan id_useria GET:llä usernamea käyttäen
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
    // Luetaan saatu json objekti ja talletetaan arvo
    qDebug()<<"onko fetchslot "+logged_un;
    fetch_userid_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(fetch_userid_data);
    QJsonObject json_obj = json_doc.object();
    userid = QString::number(json_obj["id_user"].toInt());
    qDebug()<<"Asiakkaan id on: " +userid;

    //Kutsutaan funktio jonka avulla asetetaan haettu id_user sekä selvitetään kytkettyjen tilien määrä
    fetchHowManyAcc();

    reply->deleteLater();
    userIdManager->deleteLater();
}

void MainWindow::fetchHowManyAcc()
{
    // GET:llä haetaan ne kaikki tilikytkökset joihin on kyseinen id_user kytketty
    qDebug()<<"Asiakkaan arvo edelleen:" + userid;
    QString site_url=MyUrl::getBaseUrl()+"/account_right/"+userid;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    fetchAccManager = new QNetworkAccessManager(this);

    connect(fetchAccManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(fetchHowManyAccSlot(QNetworkReply*)));

    reply = fetchAccManager->get(request);
}

void MainWindow::fetchHowManyAccSlot(QNetworkReply *reply)
{
    //Lähdetään tarkistamaan kuinka monta tiliä on kytketty ja otetaan id_account talteen
     fetch_acc_amount_data=reply->readAll();
     qDebug()<<"DATA : "+fetch_acc_amount_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(fetch_acc_amount_data);
     QJsonArray json_array = json_doc.array();
     QString total_userids;
     QStringList account_ids;
     QString acc_ids = "";

     foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        total_userids += QString::number(json_obj["id_user"].toInt());
        account_ids << QString::number(json_obj["id_account"].toInt());
     }
     account_id_1 = account_ids.at(0);
     account_id_2 = account_ids.at(1);

     qDebug()<<total_userids;
     qDebug()<<account_ids;
     qDebug()<< "1. Account_id on: " +account_id_1;
     qDebug()<< "2. Account_id on: " +account_id_2;

     //Tarkistetaan kuinka monta kertaa id_user on mainittu...
     connected_accounts = total_userids.count(userid);
     qDebug()<< total_userids.count(userid);

     //...ja suoritetaan tuloksen mukainen sivunvaihto
     switch(connected_accounts) {
         case 1:
             ui->stackedWidget->setCurrentIndex(4);
             timer->start(30000);
         case 2:
             ui->stackedWidget->setCurrentIndex(3);
             timer->start(30000);
     }

     reply->deleteLater();
     fetchAccManager->deleteLater();
}

