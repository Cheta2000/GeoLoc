#include "app.h"

App::App()
{
    dbManager = std::make_unique<DbManager>();
    apiManager = std::make_unique<ApiManager>();
    mainWindow = std::make_unique<MainWindow>();

    connect(mainWindow->button1, &QPushButton::clicked, this, &App::onAddButtonClicked);
    connect(mainWindow->button2, &QPushButton::clicked, this, &App::onDeleteButtonClicked);
    connect(mainWindow->button3, &QPushButton::clicked, this, &App::onGetButtonClicked);

    connect(apiManager.get(), &ApiManager::dataReceived, this, &App::onApiDataReceived);
    connect(apiManager.get(), &ApiManager::errorOccurred, this, &App::onApiError);

    connect(dbManager.get(), &DbManager::errorOccurred, this, &App::onDatabaseError);
    connect(dbManager.get(), &DbManager::success, this, &App::onDatabaseSuccess);
    connect(dbManager.get(), &DbManager::dataRetrieved, this, &App::onDatabaseDataRetrieved);
}

void App::onAddButtonClicked()
{
    QString data = mainWindow->getTextInput();

    if (!data.isEmpty())
    {
        mainWindow->setResultText("[STATUS] Requesting geolocation for: " + data);
        QCoreApplication::processEvents();
        apiManager->fetchGeolocationData(data);
    }
    else
    {
        onAppError("Input field is empty!");
    }
}

void App::onApiDataReceived(const QString &ip_or_url, const QString &country, const QString &city, double latitude, double longitude)
{
    if (!ip_or_url.isEmpty() && !country.isEmpty() && !city.isEmpty() && !std::isnan(latitude) && !std::isnan(longitude))
    {
        dbManager->saveData(ip_or_url, country, city, latitude, longitude);
    }
    else
    {
        onAppError("Invalid API response");
    }
}

void App::onDeleteButtonClicked()
{
    QString data = mainWindow->getTextInput();

    if (!data.isEmpty())
    {
        dbManager->deleteData(data);
    }
    else
    {
        onAppError("Input field is empty!");
    }
}

void App::onGetButtonClicked()
{
    QString data = mainWindow->getTextInput();

    if (!data.isEmpty())
    {
        dbManager->getData(data);
    }
    else
    {
        onAppError("Input field is empty!");
    }
}

void App::onDatabaseSuccess(const QString &result)
{
    mainWindow->setResultText("[SUCCESS] " + result);
}

void App::onDatabaseDataRetrieved(const QString &country, const QString &city, double latitude, double longitude)
{
    QString result = QString("Country: %1\nCity: %2\nLatitude: %3\nLongitude: %4")
                         .arg(country)
                         .arg(city)
                         .arg(latitude)
                         .arg(longitude);
    mainWindow->setResultText(result);
}

void App::onApiError(const QString &error)
{
    mainWindow->setResultText("[API ERROR] " + error);
}

void App::onDatabaseError(const QString &error)
{
    mainWindow->setResultText("[DATABASE ERROR] " + error);
}

void App::onAppError(const QString &error)
{
    mainWindow->setResultText("[APP ERROR] " + error);
}

void App::run()
{
    mainWindow->show();
}
