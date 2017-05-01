#include "RemoteListModel.h"

class MyFileInfo
{
public:
    MyFileInfo(QString name, qlonglong size, QDateTime lastModified): fileName(name), fileSize(size), fileLastModified(lastModified)
    {}
    ~MyFileInfo()
    {}

    QString getFileName() const
    {
        return fileName;
    }

    //QVariant supports qlonglong and qulonglong. As the documentation says, these are the same as qint64 and quint64.
    qlonglong getFileSize() const
    {
        return fileSize;
    }

    QDateTime getFileLastModified() const
    {
        return fileLastModified;
    }

    void setFileName(QString fileName)
    {
        this->fileName = fileName;
    }

    void setFileSize(qlonglong fileSize)
    {
        this->fileSize = fileSize;
    }

    void setFileLastModified(QDateTime fileLastModified)
    {
        this->fileLastModified = fileLastModified;
    }

private:
    QString fileName;
    qlonglong fileSize;
    QDateTime fileLastModified;
};

RemoteListModel::RemoteListModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    iconProvider = new QFileIconProvider();
    filesList = new QList<MyFileInfo>();
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

int RemoteListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return COLUMNS_COUNT;
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

QModelIndex RemoteListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid()) return QModelIndex();

    if(row >= filesList->size() || column >= COLUMNS_COUNT || column < 0 || row < 0)
        return QModelIndex();

    return createIndex(row, column, nullptr);
}

QModelIndex RemoteListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}


bool RemoteListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if (data(index, role) != value)
        {
            MyFileInfo file = filesList->at(index.row());
            switch (index.column())
            {
                case 0:
                    file.setFileName(value.toString());
                    break;
                case 1:
                    file.setFileSize(value.toLongLong());
                    break;
                case 2:
                    file.setFileLastModified(value.toDateTime());
                    break;
            }
            emit dataChanged(index, index);
            return true;
        }
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
    //flags |= Qt::ItemIsDragEnabled;
    if (index.column() == 0)
    {
       flags |= Qt::ItemIsEditable;
    }
    return flags;
}

// Calling beginInsertRows() and endInsertRows() to notify other components that the model has changed.
bool RemoteListModel::insertRows(QList<MyFileInfo> *newFiles, int count)
{
    int filesCount = filesList->size();

    if(!connected() || count < 1)
        return false;

    beginInsertRows(QModelIndex(), filesCount, filesCount + count - 1);
    for(int i = 0; i < newFiles->size(); ++i)
    {
        MyFileInfo file = newFiles->at(i);
        int idx = findFile(file.getFileName());
        if(idx != -1)
            filesList->replace(idx, file);
        else
            filesList->append(file);
    }
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

bool RemoteListModel::connectToSystem(QString &login, QString &password, QString &address)
{
    if(login == adminLogin && password == adminPassword)
    {
        isConnected = true;
        this->login = login;
        this->passwd = password;
        this->address = address;
        QList<MyFileInfo> *list = getFilesFromSystem();
        insertRows(list, list->size());
        delete list;
    }
    return isConnected;
}

int RemoteListModel::findFile(QString fileName) const
{
    for(int i = 0; i < filesList->size(); ++i)
    {
        if(filesList->at(i).getFileName() == fileName)
            return i;
    }
    return -1;
}

QList<MyFileInfo>* RemoteListModel::getFilesFromSystem()
{
    QList<MyFileInfo>* list = new QList<MyFileInfo>();
    for(int i = 0; i < 5; ++i)
    {
        MyFileInfo file(QString("File") + QString::number(i), (qlonglong)i*1024 , QDateTime::currentDateTime());
        //QMessageBox::information(NULL, "", file.getFileName());
        list->append(file);
    }
    return list;
}

QString RemoteListModel::fileName(const QModelIndex &index) const
{
    if (!connected())
        return QString();
    return filesList->at(index.row()).getFileName();
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

    const MyFileInfo &file = filesList->at(index.row());
    qlonglong bytes = file.getFileSize();
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

    const MyFileInfo &file = filesList->at(index.row());

    return file.getFileLastModified().toString(Qt::LocalDate);
}

QString RemoteListModel::userLogin() const
{
    return login;
}

QString RemoteListModel::userPasswd() const
{
    return passwd;
}

QString RemoteListModel::systemAddress() const
{
    return address;
}

