#include <QtTest>
#include "main_window.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testUIElements();
    void testButtonAdd();
    void testButtonDelete();
    void testButtonSearch();
    void testTextInput();
    void cleanupTestCase();

private:
    MainWindow *mainWindow;
};

void TestMainWindow::initTestCase()
{
    // Initialize the MainWindow instance
    mainWindow = new MainWindow();
    mainWindow->show();
}

void TestMainWindow::testUIElements()
{
    // Check if essential UI elements exist
    QVERIFY(mainWindow->findChild<QLineEdit *>("textField") != nullptr);
    QVERIFY(mainWindow->findChild<QPushButton *>("button1") != nullptr); // ADD button
    QVERIFY(mainWindow->findChild<QPushButton *>("button2") != nullptr); // DELETE button
    QVERIFY(mainWindow->findChild<QPushButton *>("button3") != nullptr); // SEARCH button
    QVERIFY(mainWindow->findChild<QLabel *>("resultLabel") != nullptr);
}

void TestMainWindow::testButtonAdd()
{
    // Simulate clicking the "ADD" button and check if appropriate behavior occurs
    QLineEdit *inputField = mainWindow->findChild<QLineEdit *>("textField");
    QPushButton *addButton = mainWindow->findChild<QPushButton *>("button1");
    QLabel *resultLabel = mainWindow->findChild<QLabel *>("resultLabel");

    inputField->setText("192.168.0.1");
    QTest::mouseClick(addButton, Qt::LeftButton);

    // Add your expected behavior after the button is clicked
    QVERIFY(resultLabel->text().contains("Added")); // Replace with actual behavior
}

void TestMainWindow::testButtonDelete()
{
    // Simulate clicking the "DELETE" button
    QPushButton *deleteButton = mainWindow->findChild<QPushButton *>("button2");
    QLabel *resultLabel = mainWindow->findChild<QLabel *>("resultLabel");

    QTest::mouseClick(deleteButton, Qt::LeftButton);

    // Add your expected behavior after the delete button is clicked
    QVERIFY(resultLabel->text().contains("Deleted")); // Replace with actual behavior
}

void TestMainWindow::testButtonSearch()
{
    // Simulate clicking the "SEARCH" button
    QPushButton *searchButton = mainWindow->findChild<QPushButton *>("button3");
    QLabel *resultLabel = mainWindow->findChild<QLabel *>("resultLabel");

    QTest::mouseClick(searchButton, Qt::LeftButton);

    // Add your expected behavior after the search button is clicked
    QVERIFY(resultLabel->text().contains("Search Results")); // Replace with actual behavior
}

void TestMainWindow::testTextInput()
{
    // Test if the text input is correctly retrieved
    QLineEdit *inputField = mainWindow->findChild<QLineEdit *>("textField");
    inputField->setText("192.168.0.1");

    QCOMPARE(mainWindow->getTextInput(), QString("192.168.0.1"));
}

void TestMainWindow::cleanupTestCase()
{
    // Cleanup if necessary
    delete mainWindow;
}

QTEST_MAIN(TestMainWindow)
#include "ui_test.moc"
