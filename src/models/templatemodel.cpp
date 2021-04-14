#include "templatemodel.hpp"


TemplateModel::TemplateModel(QObject *parent) : QAbstractListModel(parent)
{
}

TemplateModel::~TemplateModel()
{
    clearData();
}

int TemplateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_templates.size();
}

QVariant TemplateModel::data(const QModelIndex &index, int role) const
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
        }
    }

    return wrapper;
}

Template *TemplateModel::at(const quint32 &index)
{
    Template* templatee = nullptr;
    if(index >= 0 && index < m_templates.size())
    {
        templatee = m_templates.at(index);
    }
    return templatee;
}

Template *TemplateModel::get(const quint64 &guid)
{
    Template* templatee = nullptr;
    auto obj = std::find_if(m_templates.begin(), m_templates.end(),[guid](Template* o) { return o->guid() == guid; });
    if(obj != m_templates.end()) {
        templatee = *obj;
    }
    return templatee;
}

void TemplateModel::templatesReset(const QList<Template*> templates)
{
    beginResetModel();
    clearData();
    m_templates.clear();
    m_templates.append(templates);
    endResetModel();
    emit countChanged(m_templates.size());
}

void TemplateModel::insertTemplate(Template *templatee)
{
    beginInsertRows(QModelIndex(), m_templates.size(), m_templates.size());
    m_templates.append(templatee);
    endInsertRows();
    emit countChanged(m_templates.size());
}

void TemplateModel::deleteTemplate(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    m_templates.removeAt(index);
    endRemoveRows();
    emit countChanged(m_templates.size());
}

QHash<int, QByteArray> TemplateModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[NameRole] = QByteArrayLiteral("name");
    roles[DescriptionRole] = QByteArrayLiteral("description");
    roles[UseWrapperDirectoryRole] = QByteArrayLiteral("useWrapperDirectory");
    roles[WrapperDirectoryNamePatternRole] = QByteArrayLiteral("wrapperDirectoryNamePattern");
    roles[WrapperDirectoryPrefixRole] = QByteArrayLiteral("wrapperDirectoryPrefix");
    roles[ResourceFileNamePatternRole] = QByteArrayLiteral("resourceFileNamePattern");
    return roles;
}

void TemplateModel::clearData()
{
    if(!m_templates.isEmpty())
    {
        for (int i = 0; i < m_templates.size(); ++i) {
            Template* templatee;
            templatee = m_templates.at(i);
            templatee->deleteLater();
            templatee = nullptr;
        }
    }
}
