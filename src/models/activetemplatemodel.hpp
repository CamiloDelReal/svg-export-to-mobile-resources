#ifndef ACTIVETEMPLATEMODEL_HPP
#define ACTIVETEMPLATEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "template.hpp"
#include "sizemodel.hpp"

class ActiveTemplateModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum ActiveTemplateModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        UseWrapperDirectoryRole,
        WrapperDirectoryNamePatternRole,
        WrapperDirectoryPrefixRole,
        ResourceFileNamePatternRole,
        SizesRole,
        SizeModelRole
    };

    explicit ActiveTemplateModel(QObject *parent = nullptr);
    ~ActiveTemplateModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Template* at(const quint32 &index);
    Template* get(const quint64 &guid);

public slots:
    void insertTemplate(Template *templatee);
    void deleteTemplate(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Template*> m_templates;
    QList<SizeModel*> m_models;

    void clearData();
};

#endif // ACTIVETEMPLATEMODEL_HPP
