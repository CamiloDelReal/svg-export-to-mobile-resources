#include "activetemplatemodel.hpp"


ActiveTemplateModel::ActiveTemplateModel(QObject *parent) : QAbstractListModel(parent)
{
}

ActiveTemplateModel::~ActiveTemplateModel()
{
    clearData();
}

int ActiveTemplateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_templates.size();
}

QVariant ActiveTemplateModel::data(const QModelIndex &index, int role) const
{
    QVariant wrapper;

    if(index.row() >= 0 && index.row() < m_templates.size())
    {
        const Template* const item = m_templates.at(index.row());

        switch(role)
        {
        case GuidRole:
            wrapper.setValue(item->guid());
            break;
        case NameRole:
            wrapper.setValue(item->name());
            break;
        case DescriptionRole:
            wrapper.setValue(item->description());
            break;
        case UseWrapperDirectoryRole:
            wrapper.setValue(item->useWrapperDirectory());
            break;
        case WrapperDirectoryNamePatternRole:
            wrapper.setValue(item->wrapperDirectoryNamePattern());
            break;
        case WrapperDirectoryPrefixRole:
            wrapper.setValue(item->wrapperDirectoryPrefix());
            break;
        case ResourceFileNamePatternRole:
            wrapper.setValue(item->resourceFileNamePattern());
            break;
        case SizesRole:
            wrapper.setValue(item->sizes());
            break;
        case SizeModelRole:
            wrapper.setValue(m_models.at(index.row()));
            break;
        }
    }

    return wrapper;
}

Template *ActiveTemplateModel::at(const quint32 &index)
{
    Template* templatee = nullptr;
    if(index >= 0 && index < m_templates.size())
    {
        templatee = m_templates.at(index);
    }
    return templatee;
}

Template *ActiveTemplateModel::get(const quint64 &guid)
{
    Template* templatee = nullptr;
    auto obj = std::find_if(m_templates.begin(), m_templates.end(),[guid](Template* o) { return o->guid() == guid; });
    if(obj != m_templates.end()) {
        templatee = *obj;
    }
    return templatee;
}

void ActiveTemplateModel::insertTemplate(Template *templatee)
{
    beginInsertRows(QModelIndex(), m_templates.size(), m_templates.size());
    m_templates.append(templatee);
    SizeModel* model = new SizeModel();
    model->sizesReset(templatee->sizes());
    m_models.append(model);
    endInsertRows();
    emit countChanged(m_templates.size());
}

void ActiveTemplateModel::deleteTemplate(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    m_templates.removeAt(index);
    SizeModel* model = m_models.at(index);
    model->deleteLater();
    model = nullptr;
    endRemoveRows();
    emit countChanged(m_templates.size());
}

QHash<int, QByteArray> ActiveTemplateModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[NameRole] = QByteArrayLiteral("name");
    roles[DescriptionRole] = QByteArrayLiteral("description");
    roles[UseWrapperDirectoryRole] = QByteArrayLiteral("useWrapperDirectory");
    roles[WrapperDirectoryNamePatternRole] = QByteArrayLiteral("wrapperDirectoryNamePattern");
    roles[WrapperDirectoryPrefixRole] = QByteArrayLiteral("wrapperDirectoryPrefix");
    roles[ResourceFileNamePatternRole] = QByteArrayLiteral("resourceFileNamePattern");
    roles[SizesRole] = QByteArrayLiteral("sizes");
    roles[SizeModelRole] = QByteArrayLiteral("sizeModel");
    return roles;
}

void ActiveTemplateModel::clearData()
{
    if(!m_templates.isEmpty())
    {
        for (int i = 0; i < m_templates.size(); ++i) {
            Template* templatee;
            templatee = m_templates.at(i);
            templatee->deleteLater();
            templatee = nullptr;
            SizeModel* model;
            model = m_models.at(i);
            model->deleteLater();
            model = nullptr;
        }
    }
}
