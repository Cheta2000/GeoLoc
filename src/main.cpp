#include <QApplication>
#include "app.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    App myApp;
    myApp.run(); // Initializes and runs the application logic

    return app.exec();
}
