#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ApiManager : public QObject
{
    Q_OBJECT

public:
    ApiManager(QObject *parent = nullptr);
    void fetchGeolocationData(const QString &ipOrUrl);

signals:
    void dataReceived(QString ip_or_url, QString country, QString city, double latitude, double longitude);
    void errorOccurred(const QString &errorString);

private slots:
    void onResponse(QNetworkReply *reply);

private:
    QString ipOrUrl;
    QNetworkAccessManager *networkManager;
    QString apiKey;
};

#endif // APIMANAGER_H
