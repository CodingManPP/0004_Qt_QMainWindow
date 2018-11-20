#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMimeData>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //容许主窗口接收放下事件
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*拖动进入事件*/
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()){      //如果事件中存在url
        event->acceptProposedAction();      //接收动作
    }else {
        event->ignore();                    //忽略该事件
    }
}

/*放下事件*/
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();             //获取MIME数据
    if (mimeData->hasUrls()){                                  //数据中包含URL
        QList<QUrl> urlList = mimeData->urls();                 //获取URL列表
        qDebug()<<"url列表"<<urlList;
        QString fileName = urlList.at(0).toLocalFile();         //URL列表中的第一个URL是本地文件路径，转化为本地文件路径
        if (!fileName.isEmpty()){
            QFile file(fileName);                               //建立QFile对象并且以只读方式打开该文件
            if (!file.open(QIODevice::ReadOnly)){
                return ;
            }
            QTextStream in(&file);                              //建立文本流
            ui->textEdit->setText(in.readAll());                //将文件的所有内容读入到编辑器中
        }
    }
}















