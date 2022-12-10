#include "login.h"

Login::Login()
{

}

QString Login::login_function(QString un, QString pc)
{
    QJsonObject jsonObj;
    jsonObj.insert("id_student",un);
    jsonObj.insert("pin_code",pc);

    QString site_url=MyUrl::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

void Login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;

    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
        }
        else {
            if(test==0){
                ui->textIdStudent->clear();
                ui->textPassword->clear();
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
            }
            else {
                objectStudentWindow=new StudentWindow(id_student, this);
                objectStudentWindow->setWebToken("Bearer "+response_data);
                objectStudentWindow->show();
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();

}

Footer
© 2022 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
