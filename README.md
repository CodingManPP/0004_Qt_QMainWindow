# 0004_Qt_QMainWindow
Qt中的MainWindow例程

## _001_QMainWindow
### 添加子菜单
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

### 使用QActionGroup增加互斥的选择菜单
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
