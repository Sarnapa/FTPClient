#include "RemoteListModel.h"

RemoteListModel::RemoteListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    iconProvider = new QFileIconProvider();
    filesList = new QList<QFileInfo>();
}

RemoteListModel::~RemoteListModel()
{
    delete iconProvider;
    delete filesList;
}

QVariant RemoteListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // DisplayRole - The key data to be rendered in the form of text. (QString)
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
       switch (section)
       {
           case 0: return "Name";
           case 1: return "Size";
           case 2: return "Date Modified";
       }
    }
    return QVariant();
}

int RemoteListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (!connected() || parent.isValid())
        return 0;
    return filesList->size();
}

//Returns the data stored under the given role for the item referred to by the index.
QVariant RemoteListModel::data(const QModelIndex &index, int role) const
{
    if (!connected() || !index.isValid())
        return QVariant();

    switch (role)
    {
       case Qt::DisplayRole:
           switch (index.column())
           {
               case 0: return fileName(index);
               case 1: return fileSize(index);
               case 2: return lastModifiedDate(index);
           }
           break;
       case Qt::EditRole:
           switch (index.column())
           {
               case 0: return fileName(index);
               case 1: return fileSize(index);
               case 2: return lastModifiedDate(index);
           }
           break;
       case Qt::DecorationRole:
           if (index.column() == 0)
               return fileIcon(index);
           break;
       }

    return QVariant();
}

// Sets the role data for the item at index to value.
bool RemoteListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

// Returns the item flags for the given index.
// Item flags desribe the properties of an item (can be selected, edited, dragged etc)
// Flag value is power of two.
// The ItemFlags type is a typedef for QFlags<ItemFlag>. It stores an OR combination of ItemFlag values.
Qt::ItemFlags RemoteListModel::flags(const QModelIndex &index) const
{
    if (!connected() || !index.isValid())
        return Qt::NoItemFlags;

    // The default implementation from QAbstractTableModel returns Qt::ItemIsSelectable | Qt::ItemIsEnabled.
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsDragEnabled;
    if (index.column() == 0)
    {
       flags |= Qt::ItemIsEditable;
    }
    return flags;
}

// Calling beginInsertRows() and endInsertRows() to notify other components that the model has changed.
bool RemoteListModel::insertRows(QList<QFileInfo> *newFiles, int count)
{
    int filesCount = filesList->size();

    if(!connected() || count < 1)
        return false;

    beginInsertRows(QModelIndex(), filesCount, filesCount + count - 1);
    for(int i = 0; i < newFiles->size(); ++i)
        filesList->append(newFiles->at(i));
    endInsertRows();

    return true;
}

bool RemoteListModel::removeRow(QString fileName)
{
    int filesCount = filesList->size();

    if(!connected() || filesCount < 1)
        return false;

    beginInsertRows(QModelIndex(), filesCount, filesCount);
    filesList->removeAt(findFile(fileName));
    endInsertRows();

    return true;
}

int RemoteListModel::findFile(QString fileName) const
{
    for(int i = 0; i < filesList->size(); ++i)
    {
        if(filesList->at(i).fileName() == fileName)
            return i;
    }
    return -1;
}

QString RemoteListModel::fileName(const QModelIndex &index) const
{
    if (!connected())
        return QString();
    return filesList->at(index.row()).fileName();
}

QIcon RemoteListModel::fileIcon(const QModelIndex &index) const
{
    if (!connected() || !index.isValid())
        return QIcon();
    return iconProvider->icon(QFileIconProvider::File);
}

QString RemoteListModel::fileSize(const QModelIndex &index) const
{
    if (!connected())
        return QString();

    const QFileInfo &file = filesList->at(index.row());
    quint64 bytes = file.size();
    if (bytes >= 1000000000)
        return QLocale().toString(bytes / 1000000000) + QString(" GB");
    if (bytes >= 1000000)
        return QLocale().toString(bytes / 1000000) + QString(" MB");
    if (bytes >= 1000)
        return QLocale().toString(bytes / 1000) + QString(" KB");
    return QLocale().toString(bytes) + QString(" bytes");
}

QString RemoteListModel::lastModifiedDate(const QModelIndex &index) const
{
    if (!connected())
        return QString();

    const QFileInfo &file = filesList->at(index.row());

    return file.lastModified().toString(Qt::LocalDate);
}
