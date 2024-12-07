#include <QtTest>
#include "api_manager.h"
#include <QProcessEnvironment>

class TestApiManager : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {

        apiManager = new ApiManager(this);
    }

    void testFetchGeolocationData()
    {
        QSignalSpy dataReceivedSpy(apiManager, &ApiManager::dataReceived);
        QSignalSpy errorOccurredSpy(apiManager, &ApiManager::errorOccurred);

        apiManager->fetchGeolocationData("8.8.8.8");

        QVERIFY(dataReceivedSpy.wait(5000));
        QCOMPARE(errorOccurredSpy.count(), 0);

        QVERIFY(dataReceivedSpy.count() > 0);
        QList<QVariant> arguments = dataReceivedSpy.takeFirst();
        QCOMPARE(arguments.at(0).toString(), "8.8.8.8");
        QVERIFY(arguments.at(1).toString().length() > 0);
        QVERIFY(arguments.at(2).toString().length() > 0);
    }

    void testFetchGeolocationDataWithInvalidApiKey()
    {
        QSignalSpy errorOccurredSpy(apiManager, &ApiManager::errorOccurred);

        apiManager->fetchGeolocationData("invalidURL");

        QVERIFY(errorOccurredSpy.wait(1000));
        QCOMPARE(errorOccurredSpy.count(), 1);

        QList<QVariant> arguments = errorOccurredSpy.takeFirst();
        QCOMPARE(arguments.at(0).toString(), "Invalid response from API");
    }

    void cleanupTestCase()
    {
        delete apiManager;
    }

private:
    ApiManager *apiManager;
};

QTEST_MAIN(TestApiManager)
#include "api_test.moc"
