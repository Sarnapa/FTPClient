#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    localModel = new QFileSystemModel(this);
    localModel->setRootPath("C:/");
    ui->localView->setModel(localModel);
    remoteModel = new RemoteListModel(this);
    ui->remoteView->setModel(remoteModel);

    //connect(, SIGNAL(), this, SLOT(connectToSystem(QString&,QString&,QString&))
}

MainWindow::~MainWindow()
{
    delete localModel;
    delete remoteModel;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    LoggingForm *logForm = new LoggingForm(this);
    logForm->show();
}

void MainWindow::on_actionDisconnect_triggered()
{

}

void MainWindow::on_actionRefresh_triggered()
{

}

void MainWindow::on_actionRename_triggered()
{

}

void MainWindow::on_actionDelete_triggered()
{

}

void MainWindow::on_actionCancel_triggered()
{

}

void MainWindow::connectToSystem(QString &login, QString &password, QString &address)
{
    QMessageBox::information(this, "lol", login + " " + password + " " + address);
}
