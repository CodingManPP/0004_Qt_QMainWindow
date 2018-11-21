#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *action_print = new QAction(tr("打印"),this);
    QAction *action_printPreview = new QAction(tr("打印预览"),this);
    QAction *action_pdf = new QAction(tr("生成pdf"),this);

    connect(action_print,SIGNAL(triggered()),this,SLOT(doPrint()));
    connect(action_printPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
    connect(action_pdf,SIGNAL(triggered()),this,SLOT(createPdf()));

    ui->mainToolBar->addAction(action_print);
    ui->mainToolBar->addAction(action_printPreview);
    ui->mainToolBar->addAction(action_pdf);







}

MainWindow::~MainWindow()
{
    delete ui;
}

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




















