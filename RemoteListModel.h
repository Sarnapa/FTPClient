#ifndef REMOTELISTMODEL_H
#define REMOTELISTMODEL_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QList>
#include <QFileIconProvider>
#include <QLocale>
#include <QDateTime>

class RemoteListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit RemoteListModel(QObject *parent = 0);
    ~RemoteListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(QList<QFileInfo> *newFiles, int count);

    // Remove data:
    bool removeRow(QString fileName);

    inline bool connected() const
    {
      return isConnected;
    }

    QString fileName(const QModelIndex &index) const;
    QIcon fileIcon(const QModelIndex &index) const;
    QString fileSize(const QModelIndex &index) const;
    QString lastModifiedDate(const QModelIndex &index) const;

private:
    QList<QFileInfo> *filesList;
    QFileIconProvider *iconProvider;
    const QString serverPath = "";
    bool isConnected = false;

    int findFile(QString fileName) const;
};

#endif // REMOTELISTMODEL_H
