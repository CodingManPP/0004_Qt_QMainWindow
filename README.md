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

## 002_CustomAction
 自定义子菜单，使用到了自定义信号和槽的使用，比较难，需要好好琢磨，详细的源码查看工程
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_002_CustomAction/images/%E8%87%AA%E5%AE%9A%E4%B9%89%E9%83%A8%E4%BB%B6%E5%AE%9E%E4%BE%8B.gif)

## _003_RichText
### 1.使用样式
[1] 根框架使用样式 
[2] 光标使用样式
```
/**
     * 【1】根框架使用样式
     */

    QTextFrameFormat format;                                //创建框架格式
    format.setBorderBrush(Qt::red);                         //边界颜色
    format.setBorder(3);                                    //边界宽度
    QTextDocument *document = ui->textEdit->document();     //获取文档对象
    QTextFrame *rootFrame = document->rootFrame();          //获取根框架
    rootFrame->setFrameFormat(format);                      //根框架使用格式
```
效果如下：
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E6%A0%B9%E6%A1%86%E6%9E%B6%E4%BD%BF%E7%94%A8%E6%A0%B7%E5%BC%8F%E5%AE%9E%E4%BE%8B.png)
```
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
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E5%85%89%E6%A0%87%E6%A0%B7%E5%BC%8F%E6%A1%86%E6%9E%B6%E5%AE%9E%E4%BE%8B.png)
### 2.文本框内容打印
点击框架按钮，触发信号打印文本框的内容
```
    /**
     *【3-1】增加action动作，信号触发打印根框架和文本块的内容
     */
    QAction *action_textFrame = new QAction(tr("框架"),this);
    connect(action_textFrame,&QAction::triggered,this,&MainWindow::showTextFrame);
    ui->mainToolBar->addAction(action_textFrame);
```
```
/*【3-2】槽实现*/
void MainWindow::showTextFrame()
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *rootFrame = document->rootFrame();
    QTextFrame::iterator it;
    for (it = rootFrame->begin();!(it.atEnd());it++){
        QTextFrame *childFrame = it.currentFrame(); //获取当前框架的指针
        QTextBlock childBlock = it.currentBlock();  //获取当期文本块
        if (childFrame){
            qDebug()<<"frame;";
        }else if (childBlock.isValid()){
            qDebug()<<"block"<<childBlock.text();
        }
    }
}
```
【说明】这种方法只显示子框架中的文本块，无法深入到内部进行遍历
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E6%96%87%E6%9C%AC%E5%9D%97%E6%98%BE%E7%A4%BA.png)

### 3.打印所有文本内容
遍历打印所有文本框内容：
增加信号链接：
```

    /**
     *【4-1】增加action动作，信号触发打印所有文本块
     */
    QAction *action_textBlock = new QAction(tr("文本块"),this);
    connect(action_textBlock,&QAction::triggered,this,&MainWindow::showTextBlock);
    ui->mainToolBar->addAction(action_textBlock);
```
增加槽：
```
/*【4-2】槽实现*/
void MainWindow::showTextBlock()
{
    QTextDocument *document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();
    int count = document->blockCount();
    for (int i=0; i<count; i++){
        qDebug()<<tr("文本块%1，文本块首行行号为：%2，长度为：%3，内容为:").arg(i).arg(block.firstLineNumber()).arg(block.length())<<block.text();
        block = block.next();
    }
}
```
【说明】
行号是从0开始计算的；文本块的长度是从1计算的，即什么内容也不写，文本块的长度也是1，长度会比实际的字符数多1.

![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E6%89%93%E5%8D%B0%E6%89%80%E6%9C%89%E6%96%87%E6%9C%AC%E5%9D%97%E5%86%85%E5%AE%B9-%E7%A9%BA%E5%86%85%E5%AE%B9.png)

![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E6%89%93%E5%8D%B0%E6%89%80%E6%9C%89%E6%96%87%E6%9C%AC%E5%9D%97%E5%86%85%E5%AE%B9.png)

### 4.修改字体格式
增加菜单，信号触发
```
 /**
     *【5-1】增加action动作，设置字体格式
     */
    QAction *action_font = new QAction(tr("字体"),this);
    action_font->setCheckable(true);
    connect(action_font,&QAction::toggled,this,&MainWindow::setTextFont);
    ui->mainToolBar->addAction(action_font);
```
```
/*【5-2】设置字体编辑格式*/
void MainWindow::setTextFont(bool checked)
{
    if (checked){
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);                  //水平居中
        cursor.insertBlock(blockFormat);                            //使用文本格式
        QTextCharFormat charFormat;                                 //字符格式
        charFormat.setBackground(Qt::lightGray);                    //背景色
        charFormat.setForeground(Qt::blue);                         //字体颜色
        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));   //使用宋体，12号，加粗，倾斜
        charFormat.setFontUnderline(true);                          //使用下划线
        cursor.setCharFormat(charFormat);                           //使用字符格式
        cursor.insertText(tr("测试文字"));                            //插入文本
    }else{
        /*恢复默认的字体格式*/
    }
}
```
![avatar](
https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_003_RichText/myrichtext/%E5%AD%97%E4%BD%93%E6%A0%BC%E5%BC%8F%E4%BF%AE%E6%94%B9.png)

## 004_RichTextFormListImage
 富文本使用表格、列表、图片，但是图片没有显示出来
 ```
  QAction *action_textTable = new QAction(tr("表格"),this);
    QAction *action_textList = new QAction(tr("列表"),this);
    QAction *action_textImage = new QAction(tr("图片"),this);

    connect(action_textTable,&QAction::triggered,this,&MainWindow::insertTable);
    connect(action_textList,&QAction::triggered,this,&MainWindow::insertList);
    connect(action_textImage,&QAction::triggered,this,&MainWindow::insertImage);

    ui->mainToolBar->addAction(action_textTable);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textImage);
 ```
 ```
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
 ```
 
 ## 005_RichTextFind
 实现文本中的查找：主要使用的是TextEditor中的find函数
 构造方法中
 ```
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
 ```
实现槽：
```
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
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_005_RichTextFind/myrichtext/%E6%9F%A5%E6%89%BE%E5%AE%9E%E4%BE%8B%E7%BB%93%E6%9E%9C.png)

## 006_QSyntaxHighlighter
### 支持高亮
* 使用QSyntaxHighlighter类中的highlightBlock()函数
```
MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent):
    QSyntaxHighlighter(parent)
{
}
//必须重新实现该函数
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
   QTextCharFormat myFormat;                            //字符格式
   myFormat.setFontWeight(QFont::Bold);
   myFormat.setForeground(Qt::green);
   QString pattern = "\\bchar\\b";                      //要匹配的字符是“char”单词
   QRegExp expression(pattern);                         //创建正则表达式
   int index = text.indexOf(expression);
   while(index >= 0){
       int length = expression.matchedLength();
       setFormat(index,length,myFormat);                //如果匹配成功则设置格式
       index = text.indexOf(expression,index+length);   //继续匹配
   }
}

```
* 使用HTML
```
 /*使用html高亮*/
    ui->textEdit->append(tr("<h1><font color=red>使用HTML</font></h1>"));
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_006_QSyntaxHighlighter/myrichtext/%E9%AB%98%E4%BA%AEhtml.png)

## 007_DropDown
### 响应文本的拖动动作
```
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
```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_007_DropDown/mydragdrop/%E6%8B%96%E5%8A%A8%E6%94%BE%E5%85%A5%E6%98%BE%E7%A4%BA%E6%96%87%E6%9C%AC%E5%86%85%E5%AE%B9.png)

###009 打印
包含的功能：
* 打印
* 打印预览
* 生成pdf
```
/**
 * 打印功能
 */
void MainWindow::doPrint()
{
    QPrinter printer;                                                   //创建打印机对象
    QPrintDialog dialog(&printer,this);                                 //创建打印对话框
    if (ui->textEdit->textCursor().hasSelection()){                     //如果有选中区域，则只打印选中区域
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }

    if (dialog.exec() == QDialog::Accepted){                            //如果在对话框按下了打印按钮
        ui->textEdit->print(&printer);                                  //执行打印操作
    }
}

/**
 * 打印预览
 */
void MainWindow::doPrintPreview()
{
    QPrinter printer;
    QPrintPreviewDialog preview(&printer,this);                     //创建打印预览对话框
    //当要生成预览界面时，发射paintRequested()信号
    connect(&preview,&QPrintPreviewDialog::paintRequested,this,&MainWindow::printPreview);
    preview.exec();
}

/**
 * @brief MainWindow::printPreview
 */
void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

/**
 * 生成pdf
 * @brief MainWindow::createPdf
 */
void MainWindow::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("导出PDF文件"),QString(),"*pdf");
    if (!fileName.isEmpty()){
        if (QFileInfo(fileName).suffix().isEmpty()){            //如果后缀文件为空，则默认使用pdf
            fileName.append(".pdf");
        }
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);           //指定输出格式
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);

    }
}

```
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_009_print/myprint/%E6%89%93%E5%8D%B0%E7%AA%97%E5%8F%A3.png)
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_009_print/myprint/%E6%89%93%E5%8D%B0%E9%A2%84%E8%A7%88.png)
![avatar](https://github.com/CodingManPP/0004_Qt_QMainWindow/blob/master/_009_print/myprint/%E7%94%9F%E6%88%90pdf.png)
