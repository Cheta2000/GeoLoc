#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
    void setResultText(const QString &resultText);
    QString getTextInput() const;

    QLineEdit *textField;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QLabel *resultLabel;
};

#endif // MAINWINDOW_H
