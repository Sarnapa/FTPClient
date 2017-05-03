#include "TCPWorker.h"

TCPWorker::TCPWorker(QObject *parent) : QObject(parent)
{
    //receivedData = new QByteArray();
    userFiles = getFilesFromSystem();
    connect(this, SIGNAL(connectToSystemSignal(QString,QString,QString)), this, SLOT(connectToSystem(QString,QString,QString)));
    connect(this, SIGNAL(disconnectSignal()), this, SLOT(disconnect()));
    connect(this, SIGNAL(refreshSignal()), this, SLOT(refresh()));
}

TCPWorker::~TCPWorker()
{
    //delete receivedData;
    delete userFiles;
}


void TCPWorker::connectToSystem(QString login, QString password, QString address)
{
    // so far
    actionId = 0;
    if(login == adminLogin && password == adminPassword)
        isConnected = true;
}

void TCPWorker::disconnect()
{
    isConnected = false;
    emit disconnectedSignal();
}

void TCPWorker::refresh()
{
    // so far
    actionId = 1;
}

void TCPWorker::gotResponse()
{
    qDebug()<<"Worker::onTimeout get called from?: "<<QThread::currentThreadId();
    switch(actionId)
    {
        case 0:
            emit connectedToSystemSignal(isConnected, userFiles);
            break;
        case 1:
            emit refreshedSignal(isConnected, userFiles);
            break;
    }
}

QList<MyFileInfo>* TCPWorker::getFilesFromSystem() const
{
    QList<MyFileInfo>* list = new QList<MyFileInfo>();
    for(int i = 0; i < 5; ++i)
    {
        MyFileInfo file(QString("File") + QString::number(i), (qlonglong)i*1024 , QDateTime::currentDateTime());
        list->append(file);
    }
    return list;
}
