#ifndef SVGEXPORTVIEWMODEL_HPP
#define SVGEXPORTVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "templatemodel.hpp"
#include "activetemplatemodel.hpp"

#include <QDebug>


class SVGExportViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* templateModel READ templateModel NOTIFY templateModelChanged)
    Q_PROPERTY(QObject* activeTemplateModel READ activeTemplateModel NOTIFY activeTemplateModelChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString filepath READ filepath WRITE setFilepath NOTIFY filepathChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit SVGExportViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* templateModel();    
    QObject* activeTemplateModel();

    Q_INVOKABLE void readTemplates();
    Q_INVOKABLE void deleteTemplate(const quint64 &guid, const qint32 &index);

    Q_INVOKABLE bool isSVGFile(const QString &path);
    Q_INVOKABLE void loadSVG(const QString &path);

    Q_INVOKABLE QString cleanDirPath(const QString &path);

    QString filename() const;
    QString filepath() const;

    Q_INVOKABLE void addTemplate(const quint32 &index);
    Q_INVOKABLE void removeTemplate(const quint32 &index);

    Q_INVOKABLE void exportResources(const QString &outputDirectoryPath, const QVariantMap &options);

    QString error() const;

public slots:
    void setFilename(const QString &filename);
    void setFilepath(const QString &filepath);    
    void setError(const QString &error);

signals:
    void isWorkingChanged(const bool &isWorking);
    void templateModelChanged(QObject* memberModel);
    void activeTemplateModelChanged(QObject* activeTemplateModel);

    void filenameChanged(const QString &filename);
    void filepathChanged(const QString &filepath);

    void templatesReset(const QList<Template*> templates);
    void templateDeleted(const quint64 &guid, const qint32 &index);

    void errorChanged(const QString &error);

private:
    bool m_isWorking;
    TemplateModel m_templateModel;    
    ActiveTemplateModel m_activeTemplateModel;

    QString m_filename;
    QString m_filepath;

    QString m_error;

    QSqlDatabase m_appDatabase;
    XDao<Template> m_templateDao;

    static const QString SVG_EXTENSION;
    static const QString FILE_PREFFIX;

    QString buildName(const QString &pattern, const Size * const size, const QString &directoryPrefix, const QString &resourceName);
    QString buildResourceOutputFilePath(const QString &baseDirectory, const bool &useDirectoryWrapper,
                                        const QString &wrapperDirectoryPattern, const QString &resourceNamePattern,
                                        const Size * const size, const QString &directoryPrefix, const QString &resourceName);

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // SVGEXPORTVIEWMODEL_HPP
