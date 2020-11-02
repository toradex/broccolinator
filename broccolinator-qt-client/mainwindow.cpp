#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ko->setHidden(true);
    ui->ok->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFrame(QNetworkReply* reply)
{
    QPixmap pm;

    QByteArray data = reply->readAll();

    if (pm.loadFromData(data))
    {
        ui->camera->setPixmap(pm);    
    }
    delete reply;
}

void MainWindow::showError()
{
    ui->ko->setHidden(false);
    ui->ok->setHidden(true);    
    ui->type->setText("");
    ui->weight->setText("");
}

void MainWindow::showData(QString tag, int weight)
{
    ui->ko->setHidden(true);
    ui->ok->setHidden(false);    
    ui->type->setText(tag);
    ui->weight->setText(QString::number(weight));
}