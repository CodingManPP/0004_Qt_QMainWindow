#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextFrame>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**
     * 【1】根框架使用样式
     */

    QTextFrameFormat format;                                //创建框架格式
    format.setBorderBrush(Qt::red);                         //边界颜色
    format.setBorder(3);                                    //边界宽度
    QTextDocument *document = ui->textEdit->document();     //获取文档对象
    QTextFrame *rootFrame = document->rootFrame();          //获取根框架
    rootFrame->setFrameFormat(format);                      //根框架使用格式

    /**
     *【2】光标使用样式
     */
    //新建框架格式
    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);                           //设置背景颜色
    frameFormat.setMargin(10);                                          //设置外边距
    frameFormat.setPadding(5);                                          //设置内边距
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);   //设置边框样式

    QTextCursor cursor = ui->textEdit->textCursor();                    //获取光标
    cursor.insertFrame(frameFormat);                                    //应用该框架样式

}

MainWindow::~MainWindow()
{
    delete ui;
}
