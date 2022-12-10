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
        ui->stackedWidget->setCurrentIndex(2);
        timer->start(10000);
    }
    timer->start(30000);
    qDebug()<<"Timer started.";
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;
    ui->warning_label->setStyleSheet("color: red;");

    if(response_data.length()==0){
        ui->warning_label->setText(warning1);
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->warning_label->setText(warning2);
        }
        else {
            if(test==0){
                QString leftover_tries_string = QString::number(leftover_tries);
                //ui->username_input_edit->clear();
                ui->pin_input_edit->clear();
                ui->warning_label->setText(warning3 + leftover_tries_string);
            }
            // Jos kirjautumistunnukset kunnossa, siirrytään tilinvalintaan.
            else {
                timer->stop();
                ui->pin_input_edit->clear();
                ui->stackedWidget->setCurrentIndex(3);

                // WEBTOKEN LUONTI
                setWebToken("Bearer "+response_data);
                fetchAccounts();
                // yks vai kaks tiliä?
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::fetchAccounts()
{
    QString site_url=MyUrl::getBaseUrl()+"/account";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    fetchAccountManager = new QNetworkAccessManager(this);

    connect(fetchAccountManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(fetchAccountSlot(QNetworkReply*)));

    reply = fetchAccountManager->get(request);
}

void MainWindow::fetchAccountSlot(QNetworkReply *reply)
{
     response_data=reply->readAll();
     qDebug()<<"DATA : "+response_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
     QJsonArray json_array = json_doc.array();
     QString accounts;
     foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        accounts+=json_obj["account_type"].toString();
     }

     ui->label->setText(accounts);

     reply->deleteLater();
     fetchAccountManager->deleteLater();
}



void MainWindow::on_nosto20_button_clicked()
{
    QString site_url=MyUrl::getBaseUrl()+"/account";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    withdrawalManager = new QNetworkAccessManager(this);

    connect(withdrawalManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawalSlot(QNetworkReply*)));

    reply = withdrawalManager->get(request);


    /*void MainWindow::getbalance()
    {
        //HAKEE TILIN SALDON
        QString site_url="http://localhost:3000/account/"+QString::number(id_user);
        QNetworkRequest request(site_url);
        //WEBTOKEN ALKU
        QByteArray myToken="Bearer "+token.toLocal8Bit();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU
        getBalanceManager = new QNetworkAccessManager(this);
        connect(getBalanceManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
        reply = getBalanceManager->get(request);
    }*/

{
    QJsonObject jsonObj;
    jsonObj.insert("account_number",account_number);
    jsonObj.insert("balance",balance);

    jsonObj.insert("bank_name",bank_name);
    jsonObj.insert("account_type",account_type);
    jsonObj.insert("account_right",account_right);
    jsonObj.insert("account_holder",account_holder);

}
}
