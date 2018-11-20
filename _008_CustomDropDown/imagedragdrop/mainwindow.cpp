#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**/
    setAcceptDrops(true);                           //设置窗口部件可以接收拖入
    QLabel *label = new QLabel(this);               //创建Label
    QPixmap pix("../imagedragdrop/logo.png");
    label->setPixmap(pix);                          //设置图片
    label->resize(pix.size());                      //设置标签的大小为图片的大小
    label->move(100,100);
    label->setAttribute(Qt::WA_DeleteOnClose);      //当窗口关闭时销毁图片

}

MainWindow::~MainWindow()
{
    delete ui;
}

//鼠标按下事件
void MainWindow:: mousePressEvent(QMouseEvent *event)
{
    //第1步：获取图片
    //将鼠标指针所在位置的部件强制转换为QLabel类型
    QLabel *child = static_cast<QLabel *>(childAt(event->pos()));
    if (!child->inherits("QLabel")){
        return;
    }

    QPixmap pixmap = *child->pixmap();

    //第2步自定义MIME类型
    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly);
    dataStream<<pixmap<<QPoint(event->pos() - child->pos());

    //第3步：将数据放入到QMimeData
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("myimage/png",itemData);

    //第4步 将QMimeData数据放入QDrag中
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    //第5步 将原图片添加阴影
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(),QColor(127,127,127,127));
    painter.end();
    child->setPixmap(tempPixmap);

    //第6步 执行拖放操作
    if (drag->exec(Qt::CopyAction | Qt::MoveAction,Qt::CopyAction) == Qt::MoveAction){
        child->close();
    }else{
        child->show();
        child->setPixmap(pixmap);
    }
}

//拖动进入事件
void MainWindow:: dragEnterEvent(QDragEnterEvent *event)
{
    //如果有我们定义的MIME类型数据则进行移动
    if (event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }
}

//拖动事件
void MainWindow:: dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }


}
//放下事件
void MainWindow:: dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("myimage/png")){
        QByteArray itemdata = event->mimeData()->data("myimage/png");

        QDataStream dataStream(&itemdata,QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        QLabel *newLabel = new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->resize(pixmap.size());
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }

}


















