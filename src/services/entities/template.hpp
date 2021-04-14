#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Size;

class Template : public QObject, public XTableModel<Template>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool useWrapperDirectory READ useWrapperDirectory WRITE setUseWrapperDirectory NOTIFY useWrapperDirectoryChanged)
    Q_PROPERTY(QString wrapperDirectoryNamePattern READ wrapperDirectoryNamePattern WRITE setWrapperDirectoryNamePattern NOTIFY wrapperDirectoryNamePatternChanged)
    Q_PROPERTY(QString wrapperDirectoryPrefix READ wrapperDirectoryPrefix WRITE setWrapperDirectoryPrefix NOTIFY wrapperDirectoryPrefixChanged)
    Q_PROPERTY(QString resourceFileNamePattern READ resourceFileNamePattern WRITE setResourceFileNamePattern NOTIFY resourceFileNamePatternChanged)
    Q_PROPERTY(QList<Size*> sizes READ sizes WRITE setSizes NOTIFY sizesChanged)

    X_TABLE_NAME("templates")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(description),
                   X_FIELD(useWrapperDirectory),
                   X_FIELD(wrapperDirectoryNamePattern),
                   X_FIELD(wrapperDirectoryPrefix),
                   X_FIELD(resourceFileNamePattern))
    X_FOREIGN_LISTS(X_FOREIGN_LIST(Size, templateId, guid, sizes))

public:
    explicit Template(QObject *parent = nullptr);
    Template(const QString &name, QObject *parent = nullptr);
    Template(const QString &name, const QString &description, QObject *parent = nullptr);
    Template(const QString &name, const QString &description, const bool &useWrapperDirectory, const QString &wrapperDirectoryNamePattern, const QString &resourceFileNamePattern, QObject *parent = nullptr);
    Template(const Template &other);

    Template& operator=(const Template &other);

    ~Template();

    quint64 guid() const;
    QString name() const;    
    QString description() const;
    bool useWrapperDirectory() const;
    QString wrapperDirectoryNamePattern() const;    
    QString wrapperDirectoryPrefix() const;
    QString resourceFileNamePattern() const;
    QList<Size*> sizes() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);    
    void setDescription(const QString &description);
    void setUseWrapperDirectory(const bool &useWrapperDirectory);
    void setWrapperDirectoryNamePattern(const QString &wrapperDirectoryNamePattern);
    void setWrapperDirectoryPrefix(const QString &wrapperDirectoryPrefix);
    void setResourceFileNamePattern(const QString &resourceFileNamePattern);
    void setSizes(QList<Size*> sizes);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);
    void useWrapperDirectoryChanged(const bool &useWrapperDirectory);
    void wrapperDirectoryNamePatternChanged(const QString &wrapperDirectoryNamePattern);
    void wrapperDirectoryPrefixChanged(const QString &wrapperDirectoryPrefix);
    void resourceFileNamePatternChanged(const QString &resourceFileNamePattern);
    void sizesChanged(QList<Size*> sizes);    

private:
    quint64 m_guid;
    QString m_name;
    QString m_description;
    bool m_useWrapperDirectory;
    QString m_wrapperDirectoryNamePattern;
    QString m_wrapperDirectoryPrefix;
    QString m_resourceFileNamePattern;
    QList<Size*> m_sizes;

    void clearSizes();
};

#include "size.hpp"

#endif // TEMPLATE_HPP
