#include "api_manager.h"
#include <QNetworkRequest>
#include <QProcessEnvironment>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ApiManager::ApiManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    apiKey = env.value("GEO_API_KEY");

    if (apiKey.isEmpty())
    {
        emit errorOccurred("API key not found in environment variables");
    }

    connect(networkManager, &QNetworkAccessManager::finished,
            this, &ApiManager::onResponse);
}

void ApiManager::fetchGeolocationData(const QString &ipOrUrl)
{
    if (apiKey.isEmpty())
    {
        emit errorOccurred("API key is not set");

        return;
    }

    this->ipOrUrl = ipOrUrl;

    QString url = QString("http://api.ipstack.com/%1?access_key=%2").arg(ipOrUrl).arg(apiKey);
    QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
}

void ApiManager::onResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();

        QString result;
        if (jsonObject.contains("country_name") && jsonObject.contains("city") && jsonObject.contains("latitude") && jsonObject.contains("longitude"))
        {
            QString country = jsonObject.value("country_name").toString();
            QString city = jsonObject.value("city").toString();
            double latitude = jsonObject.value("latitude").toDouble();
            double longitude = jsonObject.value("longitude").toDouble();

            emit dataReceived(ipOrUrl, country, city, latitude, longitude);
        }
        else
        {
            emit errorOccurred("Invalid response from API");
        }
    }
    else
    {
        emit errorOccurred(reply->errorString());
    }

    reply->deleteLater();
}
