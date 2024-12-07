#include <QtTest/QtTest>
#include "db_manager.h"
#include <QSqlQuery>
#include <QDebug>

class TestDbManager : public QObject
{
    Q_OBJECT

public:
    TestDbManager() {}

private slots:
    void initTestCase()
    {
        dbManager = new DbManager();
        QVERIFY(dbManager != nullptr);
    }

    void cleanupTestCase()
    {
        delete dbManager;
    }

    void testSaveData()
    {
        QSignalSpy successSpy(dbManager, &DbManager::success);
        QSignalSpy errorSpy(dbManager, &DbManager::errorOccurred);

        dbManager->saveData("192.168.1.1", "USA", "New York", 40.7128, -74.0060);

        QVERIFY(successSpy.count() > 0);
        QCOMPARE(successSpy.at(0).at(0).toString(), QString("Geolocation added to the database\nCountry: USA\nCity: New York\nLatitude: 40.7128\nLongitude: -74.006"));

        QVERIFY(errorSpy.count() == 0);

        QSqlQuery query;
        query.prepare("SELECT * FROM geolocation WHERE ip_or_url = :ip_or_url");
        query.bindValue(":ip_or_url", "192.168.1.1");
        QVERIFY(query.exec());
        QVERIFY(query.next());
        QCOMPARE(query.value("country").toString(), QString("USA"));
        QCOMPARE(query.value("city").toString(), QString("New York"));
        QCOMPARE(query.value("latitude").toDouble(), 40.7128);
        QCOMPARE(query.value("longitude").toDouble(), -74.0060);
    }

    void testDeleteData()
    {
        QSignalSpy successSpy(dbManager, &DbManager::success);
        QSignalSpy errorSpy(dbManager, &DbManager::errorOccurred);

        dbManager->saveData("192.168.1.2", "Canada", "Toronto", 43.6532, -79.3832);
        dbManager->deleteData("192.168.1.2");

        QVERIFY(successSpy.count() > 0);
        QCOMPARE(successSpy.at(1).at(0).toString(), QString("Data deleted successfully"));

        QVERIFY(errorSpy.count() == 0);

        QSqlQuery query;
        query.prepare("SELECT * FROM geolocation WHERE ip_or_url = :ip_or_url");
        query.bindValue(":ip_or_url", "192.168.1.2");
        QVERIFY(query.exec());
        QVERIFY(!query.next());
    }

    void testGetData()
    {
        QSignalSpy successSpy(dbManager, &DbManager::success);
        QSignalSpy errorSpy(dbManager, &DbManager::errorOccurred);
        QSignalSpy dataRetrievedSpy(dbManager, &DbManager::dataRetrieved);

        dbManager->saveData("192.168.1.3", "Germany", "Berlin", 52.5200, 13.4050);
        dbManager->getData("192.168.1.3");

        QVERIFY(successSpy.count() > 0);
        QCOMPARE(successSpy.at(0).at(0).toString(), QString("Geolocation added to the database\nCountry: Germany\nCity: Berlin\nLatitude: 52.52\nLongitude: 13.405"));

        QVERIFY(errorSpy.count() == 0);

        QVERIFY(dataRetrievedSpy.count() > 0);
        QCOMPARE(dataRetrievedSpy.at(0).at(0).toString(), QString("Germany"));
        QCOMPARE(dataRetrievedSpy.at(0).at(1).toString(), QString("Berlin"));
        QCOMPARE(dataRetrievedSpy.at(0).at(2).toDouble(), 52.5200);
        QCOMPARE(dataRetrievedSpy.at(0).at(3).toDouble(), 13.4050);

        QSqlQuery query;
        query.prepare("SELECT * FROM geolocation WHERE ip_or_url = :ip_or_url");
        query.bindValue(":ip_or_url", "192.168.1.3");
        QVERIFY(query.exec());
        QVERIFY(query.next());
        QCOMPARE(query.value("country").toString(), QString("Germany"));
        QCOMPARE(query.value("city").toString(), QString("Berlin"));
        QCOMPARE(query.value("latitude").toDouble(), 52.5200);
        QCOMPARE(query.value("longitude").toDouble(), 13.4050);
    }

    void testGetDataNoResults()
    {
        QSignalSpy successSpy(dbManager, &DbManager::success);
        QSignalSpy errorSpy(dbManager, &DbManager::errorOccurred);
        QSignalSpy dataRetrievedSpy(dbManager, &DbManager::dataRetrieved);

        dbManager->getData("nonexistent_ip_or_url");

        QVERIFY(errorSpy.count() > 0);
        QCOMPARE(errorSpy.at(0).at(0).toString(), QString("No data found for nonexistent_ip_or_url"));

        QVERIFY(successSpy.count() == 0);

        QVERIFY(dataRetrievedSpy.count() == 0);
    }

private:
    DbManager *dbManager;
};

QTEST_MAIN(TestDbManager)
#include "db_test.moc"
