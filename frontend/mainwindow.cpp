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

    //Luodaan pääkäyttöliittymään palauttava timer
        timer2 = new QTimer(this);
        timer2->setSingleShot(true);
        connect(timer2, SIGNAL(timeout()), this, SLOT(returnToMainInterface()));
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

void MainWindow::setSaved_AccountType1(const QString &savedAT1)
{
    tallennus_at1 = savedAT1;
}
void MainWindow::setSaved_AccountNumber1(const QString &savedAN1)
{
    tallennus_an1 = savedAN1;
}
void MainWindow::setSaved_AccountType2(const QString &savedAT2)
{
    tallennus_at2 = savedAT2;
}
void MainWindow::setSaved_AccountNumber2(const QString &savedAN2)
{
    tallennus_an2 = savedAN2;
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
    fetch_user_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(fetch_user_data);
    QJsonObject json_obj = json_doc.object();
    userid = QString::number(json_obj["id_user"].toInt());
    qDebug()<<"Asiakkaan id on: " +userid;

    //Kutsutaan funktio jonka avulla asetetaan haettu id_user sekä selvitetään kytkettyjen tilien määrä
    fetchAccounts();
    //haetaan myös tähän väliin sisään kirjautuvan henkilön nimi
    fetch_user_full_name();

    QString testi = "3";
    QString testi2= "1";

    fetch_DataForCompare(testi);
    //asetetaan tilintyyppi ja -numero talteen
    setSaved_AccountType1(test_at1), setSaved_AccountNumber1(test_an1);

    qDebug()<<"tilintyyppi1:"+tallennus_at1+" ja tilinumero:"+tallennus_an1;

    fetch_DataForCompare(testi2);
    //asetetaan toinen tilityyppi ja -numero talteen
    setSaved_AccountType2(tallennus_at2), setSaved_AccountNumber2(tallennus_an2);

    qDebug()<<"tilintyyppi1.1:"+tallennus_at1+" ja tilinumero:"+tallennus_an1;
    qDebug()<<"tilintyyppi3:"+tallennus_at2+" ja tilinumero:"+tallennus_an2;

    reply->deleteLater();
    userIdManager->deleteLater();
}

void MainWindow::fetchAccounts()
{
    // GET:llä haetaan ne kaikki tilikytkökset joihin on kyseinen id_user kytketty
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

//tästä alkaa Ronin tekemät osat ---------------------------------------------------------------------------------------------------------------------------

//aikakatkaisuun liittyvä, pääkäyttöliittymään palautus
void MainWindow::returnToMainInterface()
{
    qDebug()<<"Return Timer Finished.";
    ui->stackedWidget->setCurrentIndex(4);
    //aloitetaan myös uusi 30sekunnin timer joka palauttaa käyttäjän aloitusnäytöön
    timer->start(30000);
    qDebug()<<"Timer Started.";
}
    //haetaan käyttäjän kokonimi
void MainWindow::fetch_user_full_name()
{
    QString site_url=MyUrl::getBaseUrl()+"/user/"+userid;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    fetchUserFullNameManager = new QNetworkAccessManager(this);
    connect(fetchUserFullNameManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(user_full_nameSlot(QNetworkReply*)));

    reply = fetchUserFullNameManager->get(request);
}
    //tallennetaan käyttäjän kokonimi kahteen eri muuttujaan, koska user tablessa se on eritelty user_fname, user_lname
void MainWindow::user_full_nameSlot (QNetworkReply *reply)
{

 response_user_fullname=reply->readAll();
 QJsonDocument json_doc = QJsonDocument::fromJson(response_user_fullname);
 QJsonObject json_obj = json_doc.object();

    fname=json_obj["user_fname"].toString();
    lname=json_obj["user_lname"].toString();
    qDebug()<<"käyttäjän nimi:"+fname+" "+lname;

    ui->current_user_label_1->setText(fname+ " "+ lname);
    ui->current_user_label_2->setText(fname+ " "+ lname);

    reply->deleteLater();
    fetchUserFullNameManager->deleteLater();
 }

    //haetaan kortin tyyppi ja numero vertailua varten
void MainWindow::fetch_DataForCompare(QString id)
{
    QString site_url=MyUrl::getBaseUrl()+"/account/"+id;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    CompareDataManager = new QNetworkAccessManager(this);
    connect(CompareDataManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(CompareDataSlot(QNetworkReply*)));

    reply = CompareDataManager->get(request);
}
//tallennetaan testiarvot vertailua varten muuttujiin
void MainWindow::CompareDataSlot (QNetworkReply *reply)
{

    response_CompareData=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_CompareData);
    QJsonObject json_obj = json_doc.object();

    test_at1=json_obj["account_type"].toString();
    test_an1=json_obj["account_number"].toString();

    qDebug()<<"tilintyyppi:"+test_at1+" ja tilinumero:"+test_an1;

    reply->deleteLater();
    CompareDataManager->deleteLater();

}

    //testataan onko tilin tyyppi credit vai debit
    QString MainWindow::CreditOrDebit_testing(QString a)

    {

       if(a==debit)
       {
           current_account_number=test_an1;
       }

       else
       {
           current_account_number=test_an2;
       }
       qDebug()<<"tämänhetkinen tilinumero on:"+current_account_number;
        return a;

    }



    //haetaan tilitiedot
void MainWindow::fetch_account_information()
{
    QString site_url=MyUrl::getBaseUrl()+"/account_information/"+current_account_number;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(mytn));
    //WEBTOKEN LOPPU
    account_informationManager = new QNetworkAccessManager(this);
    connect(account_informationManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(account_informationSlot(QNetworkReply*)));

    reply = account_informationManager->get(request);
}
    //tallennetaan tilitiedot muuttujiin
void MainWindow::account_informationSlot (QNetworkReply *reply)
{

 response_account_information=reply->readAll();
 QJsonDocument json_doc = QJsonDocument::fromJson(response_account_information);
 QJsonObject json_obj = json_doc.object();

    bank_name=json_obj["bank_name"].toString();
    account_holder=json_obj["account_holder"].toString();
    account_type=json_obj["account_type"].toString();
    balance=QString::number(json_obj["balance"].toDouble());
    account_number=json_obj["account_number"].toString();
    account_right=json_obj["account_right"].toString();

    //testausta

    qDebug()<<"pankin nimi:"+bank_name;
    qDebug()<<"tilin omistaja:"+account_holder;
    qDebug()<<"tilityyppi:"+account_type;
    qDebug()<<"tilin saldo:"+balance;
    qDebug()<<"tilinumero:"+account_number;
    qDebug()<<"käyttöoikeus:"+account_right;

    reply->deleteLater();
    account_informationManager->deleteLater();
 }





// tästä alaspäin nappien toimintoja
void MainWindow::on_debit_button_clicked()
{
    CreditOrDebit_testing(debit);

    ui->stackedWidget->setCurrentIndex(4);
    timer->start(30000);
    qDebug()<<"Timer Started.";
}

void MainWindow::on_credit_button_clicked()
{
    CreditOrDebit_testing(credit);

    ui->stackedWidget->setCurrentIndex(4);
    timer->start(30000);
    qDebug()<<"Timer Started.";
}

void MainWindow::on_withdraw_button_clicked()
{
    timer->stop();
    fetch_account_information();
    ui->stackedWidget->setCurrentIndex(5);
    timer2->start(10000);
    qDebug()<<"Return Timer Started.";
}

void MainWindow::on_balance_button_clicked()
{
    timer->stop();
    fetch_account_information();
    ui->stackedWidget->setCurrentIndex(8);
    timer2->start(10000);
    qDebug()<<"Return Timer Started.";
}

void MainWindow::on_transactions_button_clicked()
{
    timer->stop();
    fetch_account_information();
    ui->stackedWidget->setCurrentIndex(9);
    timer2->start(10000);
    qDebug()<<"Return Timer Started.";
}

void MainWindow::on_log_out_button_clicked()
{
    timer->stop();
    ui->stackedWidget->setCurrentIndex(0);
}

//tähän lopppuu Ronin tekemät osat -------------------------------------------------------------------------------------------------
