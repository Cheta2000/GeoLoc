#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager();
    void saveData(const QString &ip_or_url, const QString &country, const QString &city, double latitude, double longitude);
    void deleteData(const QString &ip_or_url);
    void getData(const QString &ip_or_url);

signals:
    void dataRetrieved(const QString &country, const QString &city, double latitude, double longitude);
    void success(const QString &result);
    void errorOccurred(const QString &errorString);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
