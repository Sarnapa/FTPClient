#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QMessageBox>
#include "LoggingForm.h"
#include "RemoteListModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void connectSignal(QString &login, QString &password, QString &address);

public slots:
    void connectToSystem(QString &login, QString &password, QString &address);

private:
    Ui::MainWindow *ui;

    QFileSystemModel *localModel;
    RemoteListModel *remoteModel;
    bool isConnected = false;

private slots:
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionRefresh_triggered();
    void on_actionRename_triggered();
    void on_actionDelete_triggered();
    void on_actionCancel_triggered();
};

#endif // MAINWINDOW_H
