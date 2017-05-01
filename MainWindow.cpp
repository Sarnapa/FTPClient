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
}

MainWindow::~MainWindow()
{
    delete localModel;
    delete remoteModel;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    logForm = new LoggingForm(this);
    connect(this, SIGNAL(connectSignal(QString&,QString&,QString&)), this, SLOT(connectToSystem(QString&,QString&,QString&)));
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
    if(remoteModel->connectToSystem(login, password, address))
    {
        connectionStatus = true;
        updateWindow();
        logForm->close();
    }
    else
    {
        QMessageBox::warning(logForm, "Logging Error", "Login and/or password wrong.");
    }
}

void MainWindow::updateWindow()
{
    QList<QAction *> &actionsList = ui->mainToolBar->actions();
    for(int i = 0; i < actionsList.size(); ++i)
        actionsList.at(i)->setEnabled(!actionsList.at(i)->isEnabled());
    ui->downloadButton->setEnabled(ui->downloadButton->isEnabled());
    ui->uploadButton->setEnabled(ui->uploadButton->isEnabled());
    if(connectionStatus)
    {
        statusLabel = new QLabel();
        statusLabel->setText("Connected as: " + remoteModel->userLogin());
        ui->statusBar->addPermanentWidget(statusLabel);
    }
    else
        ui->statusBar->removeWidget(statusLabel);
}
