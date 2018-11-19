#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**
     *【2】使用代码的方式添加子菜单
    */
    QMenu *editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));              //添加编辑菜单
    QAction *action_Open = editMenu->addAction(                         //添加打开菜单
                QIcon(":/image/images/open.png"),tr("打开文件(&O)"));
    action_Open->setShortcut(QKeySequence("Ctrl+O"));                   //设置快捷键
    ui->mainToolBar->addAction(action_Open);                            //在工具栏中添加动作


}

MainWindow::~MainWindow()
{
    delete ui;
}
