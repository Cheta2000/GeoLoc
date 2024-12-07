#include "db_manager.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSettings>

DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("geo_db");

    if (!db.open())
    {
        emit errorOccurred("Unable to open database: " + db.lastError().text());
    }
    else
    {
        emit success("Database connection successful");
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS geolocation ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "ip_or_url TEXT UNIQUE, "
                    "country TEXT, "
                    "city TEXT, "
                    "latitude REAL, "
                    "longitude REAL);"))
    {
        emit errorOccurred("Failed to create table: " + query.lastError().text());
    }
}

void DbManager::saveData(const QString &ip_or_url, const QString &country, const QString &city, double latitude, double longitude)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO geolocation (ip_or_url, country, city, latitude, longitude) "
                  "VALUES (:ip_or_url, :country, :city, :latitude, :longitude)");

    query.bindValue(":ip_or_url", ip_or_url);
    query.bindValue(":country", country);
    query.bindValue(":city", city);
    query.bindValue(":latitude", latitude);
    query.bindValue(":longitude", longitude);

    if (!query.exec())
    {
        emit errorOccurred("Unable to save data: " + query.lastError().text());
    }
    else
    {
        QString result = QString("Country: %1\nCity: %2\nLatitude: %3\nLongitude: %4")
                             .arg(country)
                             .arg(city)
                             .arg(latitude)
                             .arg(longitude);
        emit success("Geolocation added to the database\n" + result);
    }
}

void DbManager::deleteData(const QString &ip_or_url)
{
    QSqlQuery query;
    query.prepare("DELETE FROM geolocation WHERE ip_or_url = :ip_or_url");
    query.bindValue(":ip_or_url", ip_or_url);

    if (!query.exec())
    {
        emit errorOccurred("Unable to delete data: " + query.lastError().text());
    }
    else
    {
        emit success("Data deleted successfully");
    }
}

void DbManager::getData(const QString &ip_or_url)
{
    QSqlQuery query;
    query.prepare("SELECT country, city, latitude, longitude FROM geolocation WHERE ip_or_url = :ip_or_url");
    query.bindValue(":ip_or_url", ip_or_url);

    if (!query.exec())
    {
        emit errorOccurred("Unable to retrieve data: " + query.lastError().text());
    }
    else if (query.next())
    {
        QString country = query.value(0).toString();
        QString city = query.value(1).toString();
        double latitude = query.value(2).toDouble();
        double longitude = query.value(3).toDouble();

        emit dataRetrieved(country, city, latitude, longitude);
    }
    else
    {
        emit errorOccurred("No data found for " + ip_or_url);
    }
}
