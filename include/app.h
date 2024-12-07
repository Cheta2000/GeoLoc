#ifndef APP_H
#define APP_H

#include <QObject>
#include <QCoreApplication>
#include <memory>
#include <QString>
#include "db_manager.h"
#include "api_manager.h"
#include "main_window.h"

// class to handle communcation between ui, db and api
class App : public QObject
{
    Q_OBJECT

public:
    App();
    ~App() = default;
    void run();

private slots:
    // buttons actions
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onGetButtonClicked();
    // api actions
    void onApiDataReceived(const QString &ip_or_url, const QString &country, const QString &city, double latitude, double longitude);
    void onApiError(const QString &error);
    // database actions
    void onDatabaseError(const QString &error);
    void onDatabaseSuccess(const QString &result);
    void onDatabaseDataRetrieved(const QString &country, const QString &city, double latitude, double longitude);

private:
    std::unique_ptr<DbManager> dbManager;
    std::unique_ptr<ApiManager> apiManager;
    std::unique_ptr<MainWindow> mainWindow;

    void onAppError(const QString &error);
};

#endif // APP_H
