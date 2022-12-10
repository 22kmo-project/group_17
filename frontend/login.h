#ifndef LOGIN_H
#define LOGIN_H

#include "myurl.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class Login
{
public:
    Login();
    QString login_function(QString,QString);

private slots:
    void loginSlot (QNetworkReply *reply);

private:
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // LOGIN_H
