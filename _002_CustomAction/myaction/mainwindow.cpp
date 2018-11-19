#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myaction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyAction *action = new MyAction;
    QMenu *editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));
    editMenu->addAction(action);
    connect(action,SIGNAL(getText(QString)),this,SLOT(setText(QString)));
}

//插入文本
void MainWindow::setText(const QString &string)
{
    //将获取的文本添加到编辑器中
    ui->textEdit->setText(string);
}

MainWindow::~MainWindow()
{
    delete ui;
}
