#ifndef EXPORTDATA_HPP
#define EXPORTDATA_HPP

#include <QObject>
#include <QVariant>


class ExportData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool useWrapperDirectory READ useWrapperDirectory WRITE setUseWrapperDirectory NOTIFY useWrapperDirectoryChanged)
    Q_PROPERTY(QString wrapperDirectoryNamePattern READ wrapperDirectoryNamePattern WRITE setWrapperDirectoryNamePattern NOTIFY wrapperDirectoryNamePatternChanged)
    Q_PROPERTY(QString directoryPrefix READ directoryPrefix WRITE setDirectoryPrefix NOTIFY directoryPrefixChanged)
    Q_PROPERTY(QString resourceFileNamePattern READ resourceFileNamePattern WRITE setResourceFileNamePattern NOTIFY resourceFileNamePatternChanged)
    Q_PROPERTY(QString resourceName READ resourceName WRITE setResourceName NOTIFY resourceNameChanged)
    Q_PROPERTY(QList<bool> options READ options WRITE setOptions NOTIFY optionsChanged)

public:
    explicit ExportData(QObject *parent = nullptr);
    ExportData(const ExportData &other);

    ExportData& operator=(const ExportData &other);

    bool useWrapperDirectory() const;
    QString wrapperDirectoryNamePattern() const;
    QString directoryPrefix() const;
    QString resourceFileNamePattern() const;
    QString resourceName() const;
    QList<bool> options() const;

public slots:
    void setUseWrapperDirectory(const bool &useWrapperDirectory);
    void setWrapperDirectoryNamePattern(const QString &wrapperDirectoryNamePattern);
    void setDirectoryPrefix(const QString &directoryPrefix);
    void setResourceFileNamePattern(const QString &resourceFileNamePattern);
    void setResourceName(const QString &resourceName);
    void setOptions(const QList<bool> &options);

signals:
    void useWrapperDirectoryChanged(const bool &useWrapperDirectory);
    void wrapperDirectoryNamePatternChanged(const QString &wrapperDirectoryNamePattern);
    void directoryPrefixChanged(const QString &directoryPrefix);
    void resourceFileNamePatternChanged(const QString &resourceFileNamePattern);
    void resourceNameChanged(const QString &resourceName);
    void optionsChanged(const QList<bool> &options);

private:
    bool m_useWrapperDirectory;
    QString m_wrapperDirectoryNamePattern;
    QString m_directoryPrefix;
    QString m_resourceFileNamePattern;
    QString m_resourceName;
    QList<bool> m_options;
};
Q_DECLARE_METATYPE(ExportData*)

#endif // EXPORTDATA_HPP
