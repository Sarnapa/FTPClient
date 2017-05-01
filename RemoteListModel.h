#ifndef REMOTELISTMODEL_H
#define REMOTELISTMODEL_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QList>
#include <QFileIconProvider>
#include <QLocale>
#include <QDateTime>
#include <QMessageBox>

#define COLUMNS_COUNT 3

class MyFileInfo;

class RemoteListModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString userLogin READ userLogin)
    Q_PROPERTY(QString userPasswd READ userPasswd)
    Q_PROPERTY(QString systemAddress READ systemAddress)

public:
    explicit RemoteListModel(QObject *parent = 0);
    ~RemoteListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index = QModelIndex()) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(QList<MyFileInfo> *newFiles, int count);

    // Remove data:
    bool removeRow(QString fileName);

    bool connectToSystem(QString &login, QString &password, QString &address);
    inline bool connected() const
    {
      return isConnected;
    }

    QString fileName(const QModelIndex &index) const;
    QIcon fileIcon(const QModelIndex &index) const;
    QString fileSize(const QModelIndex &index) const;
    QString lastModifiedDate(const QModelIndex &index) const;

    QString userLogin() const;
    QString userPasswd() const;
    QString systemAddress() const;
private:
    QList<MyFileInfo> *filesList;
    QFileIconProvider *iconProvider;
    QString login = "";
    QString passwd = "";
    QString address = "";
    const QString adminLogin = "admin";
    const QString adminPassword = "admin";
    bool isConnected = false;

    int findFile(QString fileName) const;
    QList<MyFileInfo>* getFilesFromSystem();
};

#endif // REMOTELISTMODEL_H
