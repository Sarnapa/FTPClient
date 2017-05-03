#ifndef TCPWORKER_H
#define TCPWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QList>
#include <QByteArray>
#include "MyFileInfo.h"

class TCPWorker : public QObject
{
    Q_OBJECT
public:
    explicit TCPWorker(QObject *parent = 0);
    ~TCPWorker();
signals:
    void connectToSystemSignal(QString login, QString password, QString address);
    void connectedToSystemSignal(bool connected, QList<MyFileInfo> *userFiles);
    void disconnectSignal();
    void disconnectedSignal();
    void refreshSignal();
    void refreshedSignal(bool connected, QList<MyFileInfo> *userFiles);
    // for PAIN
    void onTimeout();
private:
    //QByteArray *receivedData;
    //for PAIN
    int actionId;
    bool isConnected = false;
    const QString adminLogin = "admin";
    const QString adminPassword = "admin";
    QList<MyFileInfo> *userFiles;
    QList<MyFileInfo>* getFilesFromSystem() const;
private slots:
    //void gotResponse(QByteArray *data);
    void connectToSystem(QString login, QString password, QString address);
    void disconnect();
    void refresh();
    void gotResponse();
};

#endif // TCPWORKER_H
