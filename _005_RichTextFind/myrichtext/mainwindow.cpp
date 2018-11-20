#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include <qDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *action_textFind = new QAction(tr("查找"),this);
    connect(action_textFind,&QAction::triggered,this,&MainWindow::textFind);
    ui->mainToolBar->addAction(action_textFind);

    findDialog = new QDialog(this);
    lineEdit = new QLineEdit(findDialog);
    QPushButton *btn = new QPushButton(findDialog);
    btn->setText(tr("查找下一个"));
    connect(btn,&QPushButton::clicked,this,&MainWindow::findtext);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    findDialog->setLayout(layout);

}
/*查找文本*/
void MainWindow::textFind()
{
    findDialog->show();
}

/*查找下一个*/
void MainWindow::findtext()
{
   QString string = lineEdit->text();
   //使用查找函数查找指定的字符串，查找方式是向后查找
   bool isFind = ui->textEdit->find(string,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively);
   if (isFind){
       qDebug()<< tr("行号：%1 列号：%2")
                 .arg(ui->textEdit->textCursor().blockNumber())
                 .arg(ui->textEdit->textCursor().columnNumber());
   }
}


MainWindow::~MainWindow()
{
    delete ui;
}
