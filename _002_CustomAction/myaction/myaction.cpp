#include "myaction.h"

#include <QLineEdit>
#include <QSplitter>
#include <QLabel>

MyAction::MyAction(QObject *parent):
    QWidgetAction(parent)
{
    //创建行编辑器
    lineEdit = new QLineEdit;
    //将行编辑器的按下回车键信号与发送文本槽关联
    connect(lineEdit,&QLineEdit::returnPressed,this,&MyAction::sendText);
}


//声明函数：该函数是QWidgetAction类中的虚函数
QWidget * MyAction:: createWidget(QWidget *parent)
{
    /**
     *使用inherits()函数判断父部件是否是菜单或者工具栏
     * 如果是：创建该父部件的子部件，并且返回子部件
     * 否则，直接返回0
     * 分割窗口：QSplitter类
     * 参考文章：https://www.cnblogs.com/fuqia/p/8882994.html
     */
    if (parent->inherits("QMenu")||parent->inherits("QToolBar")){
        QSplitter *splitter = new QSplitter(parent);
        QLabel *label = new QLabel;
        label->setText(tr("插入文件:"));
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }

    return 0;
}

void MyAction::sendText()
{
    emit getText(lineEdit->text()); //发射信号，将行编辑器中的内容发射出去
    lineEdit->clear();              //清空行编辑器
}
