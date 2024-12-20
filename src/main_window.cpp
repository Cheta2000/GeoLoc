#include "main_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpacerItem>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    setWindowTitle("Geolocation");
    setMinimumSize(400, 300);
    centralWidget->setStyleSheet("background-color: #f3f9fc;");

    textField = new QLineEdit(this);
    textField->setObjectName("INPUT");
    textField->setPlaceholderText("Enter URL or IP...");
    textField->setStyleSheet("QLineEdit {"
                             "    padding: 10px;"
                             "    font-size: 16px;"
                             "    border: 2px solid #ddd;"
                             "    border-radius: 5px;"
                             "    background-color: #fff;"
                             "}"
                             "QLineEdit:focus {"
                             "    border-color: #76c7c0;"
                             "}");

    button1 = new QPushButton("ADD", this);
    button1->setObjectName("ADD");
    button2 = new QPushButton("DELETE", this);
    button2->setObjectName("DELETE");
    button3 = new QPushButton("SEARCH", this);
    button3->setObjectName("SEARCH");

    QString buttonStyle = "QPushButton {"
                          "    background-color: #4CAF50;"
                          "    color: white;"
                          "    padding: 12px 20px;"
                          "    font-size: 16px;"
                          "    border-radius: 5px;"
                          "    border: none;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #45a049;"
                          "}"
                          "QPushButton:pressed {"
                          "    background-color: #3e8e41;"
                          "}";
    button1->setStyleSheet(buttonStyle);
    button2->setStyleSheet(buttonStyle);
    button3->setStyleSheet(buttonStyle);

    resultLabel = new QLabel("", this);
    resultLabel->setObjectName("RESULT");
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);
    resultLabel->setStyleSheet("color: #000; font-size: 16px; background-color: #e0f7fa; padding: 10px; border: 1px solid #76c7c0; border-radius: 5px;");

    resultLabel->setMinimumHeight(100);
    resultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Geolocation", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #333;");
    layout->addWidget(titleLabel);

    layout->addWidget(textField);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    layout->addLayout(buttonLayout);

    layout->addWidget(resultLabel);

    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer);

    setStyle(QStyleFactory::create("Fusion"));
}

void MainWindow::setResultText(const QString &resultText)
{
    resultLabel->setText(resultText);
}

QString MainWindow::getTextInput() const
{
    return textField->text();
}
