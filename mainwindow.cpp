#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dorama.h"
#include "urlparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString textEditContent = ui->textEdit->toPlainText();
    Dorama newDorama = CreateDoramaItem(textEditContent);
    ui->listWidget->addItem(newDorama);

}
