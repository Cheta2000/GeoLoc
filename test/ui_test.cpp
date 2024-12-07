#include <QtTest/QtTest>
#include "main_window.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        mainWindow = new MainWindow();
    }

    void cleanupTestCase()
    {
        delete mainWindow;
    }

    void testTextFieldInput()
    {
        QLineEdit *textField = mainWindow->findChild<QLineEdit *>("INPUT");
        QVERIFY(textField != nullptr);
        textField->setText("192.168.1.1");
        QCOMPARE(textField->text(), QString("192.168.1.1"));
    }

    void testButtonClicks()
    {
        QPushButton *button1 = mainWindow->findChild<QPushButton *>("ADD");
        QPushButton *button2 = mainWindow->findChild<QPushButton *>("DELETE");
        QPushButton *button3 = mainWindow->findChild<QPushButton *>("SEARCH");

        QVERIFY(button1 != nullptr);
        QVERIFY(button2 != nullptr);
        QVERIFY(button3 != nullptr);

        QTest::mouseClick(button1, Qt::LeftButton);
        QTest::mouseClick(button2, Qt::LeftButton);
        QTest::mouseClick(button3, Qt::LeftButton);
    }

    void testResultLabelUpdate()
    {
        QLabel *resultLabel = mainWindow->findChild<QLabel *>("RESULT");
        QVERIFY(resultLabel != nullptr);
        mainWindow->setResultText("Test result");
        QCOMPARE(resultLabel->text(), QString("Test result"));
    }

private:
    MainWindow *mainWindow;
};

QTEST_MAIN(TestMainWindow)
#include "ui_test.moc"
