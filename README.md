# 0004_Qt_QMainWindow
Qt中的MainWindow例程

## _001_QMainWindow
### 1.添加子菜单
* 【1】使用设计师添加子菜单
* 【2】使用代码添加子菜单,在mainwindow.cpp中
```
    /**
     *【2】使用代码的方式添加子菜单
    */
    QMenu *editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));              //添加编辑菜单
    QAction *action_Open = editMenu->addAction(                         //添加打开菜单
                QIcon(":/image/images/open.png"),tr("打开文件(&O)"));
    action_Open->setShortcut(QKeySequence("Ctrl+O"));                   //设置快捷键
    ui->mainToolBar->addAction(action_Open);                            //在工具栏中添加动作
```

### 2.使用QActionGroup增加互斥的选择菜单
```
/**
      * 【3】QActionGroup类
      */
    QActionGroup *group = new QActionGroup(this);                       //建立动作组
    QAction *action_L = group->addAction(tr("左对齐(&L)"));              //向动作组添加动作
    action_L->setCheckable(true);                                       //设置动作的checkable属性

    QAction *action_R = group->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);

    QAction *action_C = group->addAction(tr("居中对齐(&C)"));
    action_C->setCheckable(true);

    action_L->setChecked(true);                                         //设置action_L为默认的选中状态

    editMenu->addSeparator();                                           //向菜单中添加间隔器

    editMenu->addAction(action_L);                                      //向菜单中添加动作
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_001_QMainWindow/mymainwindow/QActionGroup%E6%95%88%E6%9E%9C.png)

### 3.工具栏的使用
增加了3个部件，原始的部件、新建了一个QToolButton和一个QSpinBox放置到了工具栏中
```
/**
  * 【4】工具栏的使用
  */
ui->mainToolBar->addSeparator();                           //向菜单中添加间隔器

QToolButton *toolBtn = new QToolButton(this);              //1.创建QToolButton
toolBtn->setText(tr("颜色"));

QMenu *colorMenu = new QMenu(this);                         //创建菜单
colorMenu->addAction(tr("红色"));
colorMenu->addAction(tr("绿色"));

toolBtn->setMenu(colorMenu);                                //添加菜单
toolBtn->setPopupMode(QToolButton::MenuButtonPopup);        //弹出模式
ui->mainToolBar->addWidget(toolBtn);                        //向工具栏中添加QToolButton按钮

ui->mainToolBar->addSeparator();                            //向菜单中添加间隔器

QSpinBox *spinBox = new QSpinBox(this);                      //2.创建QSpinBox
ui->mainToolBar->addWidget(spinBox);                         //向工具栏添加QSpinBox部件
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_001_QMainWindow/mymainwindow/%E5%B7%A5%E5%85%B7%E6%A0%8F%E7%9A%84%E4%BD%BF%E7%94%A8.png)

### 4.中心部件QMDI的实例
在MainWindow窗口添加部件QMdiArea部件，显示多窗口
```
void MainWindow::on_action_New_triggered()
{
    //新建文本编辑器部件
    QTextEdit *edit = new QTextEdit(this);
    //使用QMdiArea类的addSubWIndow()函数创建子窗口，以文本编辑器为中心部件
    QMdiSubWindow *child = ui->mdiArea->addSubWindow(edit);
    child->setWindowTitle(tr("多文档编辑器子窗口"));
    child->show();
}
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_001_QMainWindow/mymainwindow/QMdiArea%E5%A4%9A%E7%AA%97%E5%8F%A3%E4%BD%BF%E7%94%A8.png)

### 5.Dock工具箱的显示
使用信号和槽进行触发
```
//dock工具箱的显示
void MainWindow::on_action_Dock_triggered()
{
    ui->dockWidget->show();
}
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_001_QMainWindow/mymainwindow/Dock%E9%83%A8%E4%BB%B6%E6%98%BE%E7%A4%BA%E6%95%88%E6%9E%9C.png)

### 6.状态栏信息的显示
【注意】只能使用代码添加
```
    /**
      *【状态栏添加状态信息】
      */
    ui->statusBar->showMessage(tr("欢迎使用多文档编辑器"),2000);
    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("www.qter.org");
    ui->statusBar->addPermanentWidget(permanent);
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_001_QMainWindow/mymainwindow/%E7%8A%B6%E6%80%81%E6%A0%8F%E4%BF%A1%E6%81%AF%E5%AE%9E%E4%BE%8B.png)

