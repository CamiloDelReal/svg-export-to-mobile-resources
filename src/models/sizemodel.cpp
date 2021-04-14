#include "sizemodel.hpp"


SizeModel::SizeModel(QObject *parent) : QAbstractListModel(parent)
{
}

SizeModel::~SizeModel()
{
    clearData();
}

int SizeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_sizes.size();
}

QVariant SizeModel::data(const QModelIndex &index, int role) const
{
    QVariant wrapper;

    if(index.row() >= 0 && index.row() < m_sizes.size())
    {
        const Size* const item = m_sizes.at(index.row());

        switch(role)
        {
        case GuidRole:
            wrapper.setValue(item->guid());
            break;
        case LabelRole:
            wrapper.setValue(item->label());
            break;
        case ScaleRole:
            wrapper.setValue(item->scale());
            break;
        case WidthRole:
            wrapper.setValue(item->width());
            break;
        case HeightRole:
            wrapper.setValue(item->height());
            break;
        case ItemRole:
            wrapper.setValue(item);
            break;
        }
    }

    return wrapper;
}

void SizeModel::sizesReset(const QList<Size*> sizes)
{
    beginResetModel();
    clearData();
    m_sizes.clear();
    m_sizes.append(sizes);
    endResetModel();
    emit countChanged(m_sizes.size());
}

void SizeModel::insertSize(Size *size)
{
    beginInsertRows(QModelIndex(), m_sizes.size(), m_sizes.size());
    m_sizes.append(size);
    endInsertRows();
    emit countChanged(m_sizes.size());
}

void SizeModel::deleteSize(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    m_sizes.removeAt(index);
    endRemoveRows();
    emit countChanged(m_sizes.size());
}

QHash<int, QByteArray> SizeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[LabelRole] = QByteArrayLiteral("label");
    roles[ScaleRole] = QByteArrayLiteral("iconScale");
    roles[WidthRole] = QByteArrayLiteral("iconWidth");
    roles[HeightRole] = QByteArrayLiteral("iconHeight");
    roles[ItemRole] = QByteArrayLiteral("item");
    return roles;
}

void SizeModel::clearData()
{
    if(!m_sizes.isEmpty())
    {
        for (int i = 0; i < m_sizes.size(); ++i) {
            Size* size;
            size = m_sizes.at(i);
            size->deleteLater();
            size = nullptr;
        }
    }
}
