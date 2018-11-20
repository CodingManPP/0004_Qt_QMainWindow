#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//前置声明
class QLineEdit;
class QDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *lineEdit;
    QDialog *findDialog;

private slots:
    void textFind();
    void findtext();

};

#endif // MAINWINDOW_H
