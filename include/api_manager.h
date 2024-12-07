#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

// class that handles api operations
class ApiManager : public QObject
{
    Q_OBJECT

public:
    ApiManager(QObject *parent = nullptr);
    // method to request to api
    void fetchGeolocationData(const QString &ipOrUrl);

signals:
    // when api returns data
    void dataReceived(QString ip_or_url, QString country, QString city, double latitude, double longitude);
    // when api returns error
    void errorOccurred(const QString &errorString);

public slots:
    // when api response
    void onResponse(QNetworkReply *reply);

private:
    QString ipOrUrl;
    QNetworkAccessManager *networkManager;
    QString apiKey;
};

#endif // APIMANAGER_H
