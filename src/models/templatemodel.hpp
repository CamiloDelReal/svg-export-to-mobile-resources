#ifndef TEMPLATEMODEL_HPP
#define TEMPLATEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "template.hpp"


class TemplateModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum TemplateModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        UseWrapperDirectoryRole,
        WrapperDirectoryNamePatternRole,
        WrapperDirectoryPrefixRole,
        ResourceFileNamePatternRole
    };

    explicit TemplateModel(QObject *parent = nullptr);
    ~TemplateModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Template* at(const quint32 &index);
    Template* get(const quint64 &guid);

public slots:
    void templatesReset(const QList<Template*> templates);
    void insertTemplate(Template *templatee);
    void deleteTemplate(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Template*> m_templates;

    void clearData();
};

#endif // TEMPLATEMODEL_HPP
