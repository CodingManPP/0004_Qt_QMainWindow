#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *action_textTable = new QAction(tr("表格"),this);
    QAction *action_textList = new QAction(tr("列表"),this);
    QAction *action_textImage = new QAction(tr("图片"),this);

    connect(action_textTable,&QAction::triggered,this,&MainWindow::insertTable);
    connect(action_textList,&QAction::triggered,this,&MainWindow::insertList);
    connect(action_textImage,&QAction::triggered,this,&MainWindow::insertImage);

    ui->mainToolBar->addAction(action_textTable);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//[1-2]插入表格
void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellPadding(10);
    format.setCellSpacing(2);
    cursor.insertTable(2,2,format);
}

//[2-2]插入列表
void MainWindow::insertList()
{
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

//[3-2]插入图片
void MainWindow::insertImage()
{
   QTextImageFormat format;
   format.setName("../myrichtext/logo.png");
   ui->textEdit->textCursor().insertImage(format);
}















