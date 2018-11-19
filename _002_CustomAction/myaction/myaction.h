#ifndef MYACTION_H
#define MYACTION_H

#include <QWidgetAction>

class QLineEdit;  //前置声明

class MyAction : public QWidgetAction
{
    Q_OBJECT

public:
    explicit MyAction(QObject *parent = 0);

protected:
    //声明函数：该函数是QWidgetAction类中的虚函数
    QWidget * createWidget(QWidget *parent);

signals:
    //新建信号，用于在按下回车键时，将行编辑器中的内容发射出去
    void getText(const QString &string);

    //新建槽，用于与行编辑器的按下回车键信号关联
private slots:
    void sendText();

private:
    //声明行编辑器的指针
    QLineEdit *lineEdit;

};

#endif // MYACTION_H
