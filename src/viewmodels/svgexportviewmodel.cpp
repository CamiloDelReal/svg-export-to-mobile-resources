#include <QtConcurrent/QtConcurrent>
#include <QSvgRenderer>
#include <QImage>
#include <QPainter>

#include "svgexportviewmodel.hpp"
#include "databasemanager.hpp"
#include "exportdata.hpp"
#include "size.hpp"
#include "constants.hpp"


const QString SVGExportViewModel::SVG_EXTENSION = QStringLiteral("svg");
const QString SVGExportViewModel::FILE_PREFFIX = QStringLiteral("file:///");

SVGExportViewModel::SVGExportViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
    connect(this, &SVGExportViewModel::templatesReset, &m_templateModel, &TemplateModel::templatesReset);
    connect(this, &SVGExportViewModel::templateDeleted, &m_templateModel, &TemplateModel::deleteTemplate);
}

bool SVGExportViewModel::isWorking() const
{
    return m_isWorking;
}

QObject* SVGExportViewModel::templateModel()
{
    return dynamic_cast<QObject*>(&m_templateModel);
}

QObject* SVGExportViewModel::activeTemplateModel()
{
    return dynamic_cast<QObject*>(&m_activeTemplateModel);
}

void SVGExportViewModel::readTemplates()
{
    setIsWorking(true);
    SVGExportViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]() {
        viewModel->m_templateDao.setDatabase(viewModel->m_appDatabase);
        QList<Template*> templates;
        viewModel->m_templateDao.readAll(templates);
        emit viewModel->templatesReset(templates);
        viewModel->setIsWorking(false);
    });
}

void SVGExportViewModel::deleteTemplate(const quint64 &guid, const qint32 &index)
{
    setIsWorking(true);
    SVGExportViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid, index]() {
        viewModel->m_templateDao.setDatabase(viewModel->m_appDatabase);
        QVariantMap map;
        map.insert("guid", guid);
        viewModel->m_templateDao.deleteBy(map);
        emit viewModel->templateDeleted(guid, index);
        viewModel->setIsWorking(false);
    });
}

bool SVGExportViewModel::isSVGFile(const QString &path)
{
    QFileInfo info(path);
    return (info.suffix().toLower() == SVG_EXTENSION);
}

void SVGExportViewModel::loadSVG(const QString &path)
{
    QString cleanedPath;
    if(path.startsWith(FILE_PREFFIX))
        cleanedPath = path.last(path.length() - FILE_PREFFIX.length());
    else
        cleanedPath = path;
    QFileInfo info(cleanedPath);
    setFilename(info.baseName());
    setFilepath(info.absoluteFilePath());
}

QString SVGExportViewModel::cleanDirPath(const QString &path)
{
    if(path.startsWith(FILE_PREFFIX))
    {
        return path.last(path.length() - FILE_PREFFIX.length());
    }
    return path;
}

QString SVGExportViewModel::filename() const
{
    return m_filename;
}

QString SVGExportViewModel::filepath() const
{
    return m_filepath;
}

void SVGExportViewModel::addTemplate(const quint32 &index)
{
    setIsWorking(true);
    SVGExportViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, index]() {
        Template* templatee = viewModel->m_templateModel.at(index);
        if(templatee != nullptr)
        {
            viewModel->m_templateDao.setDatabase(viewModel->m_appDatabase);
            viewModel->m_templateDao.resolveForeigns(templatee);
            viewModel->m_activeTemplateModel.insertTemplate(templatee);
        }
        viewModel->setIsWorking(false);
    });
}

void SVGExportViewModel::removeTemplate(const quint32 &index)
{
    setIsWorking(true);
    SVGExportViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, index]() {
        viewModel->m_activeTemplateModel.deleteTemplate(0, index);
        viewModel->setIsWorking(false);
    });
}

void SVGExportViewModel::exportResources(const QString &outputDirectoryPath, const QVariantMap &options)
{
    setIsWorking(true);
    SVGExportViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, outputDirectoryPath, options]() {
        // Create output directory
        qDebug() << "Output dir " << outputDirectoryPath;
        QDir outputDirectory(outputDirectoryPath);
        if(!outputDirectory.exists())
        {
            outputDirectory.mkpath(outputDirectoryPath);
        }
        qDebug() << "Dir fixed  " << outputDirectory.absolutePath();
        QSvgRenderer renderer(viewModel->m_filepath);
        foreach(QString key, options.keys())
        {
            quint32 index = key.toInt();
            ExportData* exportData = static_cast<ExportData*>(options[key].value<ExportData*>());
            QList<bool> options = exportData->options();

            //Template
            Template* templatee = viewModel->m_activeTemplateModel.at(index);
            QList<Size*> sizes = templatee->sizes();

            //Sizes chosen
            for(quint32 i = 0; i < options.size(); i++)
            {
                bool chosen = options[i];
                if(chosen)
                {
                    Size* size = sizes[i];
                    QString outputFilePath = viewModel->buildResourceOutputFilePath(outputDirectoryPath,
                                                                                    exportData->useWrapperDirectory(),
                                                                                    exportData->wrapperDirectoryNamePattern(),
                                                                                    exportData->resourceFileNamePattern(),
                                                                                    size, exportData->directoryPrefix(),
                                                                                    exportData->resourceName());
                    QImage image(size->width(), size->height(), QImage::Format_ARGB32);
                    image.fill(0x00000000);
                    QPainter painter(&image);
                    renderer.render(&painter);
                    image.save(outputFilePath);
                }
            }
        }

        viewModel->setIsWorking(false);
    });
}

QString SVGExportViewModel::error() const
{
    return m_error;
}

void SVGExportViewModel::setFilename(const QString &filename)
{
    if (m_filename != filename)
    {
        m_filename = filename;
        emit filenameChanged(m_filename);
    }
}

void SVGExportViewModel::setFilepath(const QString &filepath)
{
    if (m_filepath != filepath)
    {
        m_filepath = filepath;
        emit filepathChanged(m_filepath);
    }
}

void SVGExportViewModel::setError(const QString &error)
{
    if (m_error != error)
    {
        m_error = error;
        emit errorChanged(m_error);
    }
}

QString SVGExportViewModel::buildName(const QString &pattern, const Size * const size, const QString &directoryPrefix, const QString &resourceName)
{
    QString name = pattern;
    if(name.contains(DIRECTORYPREFIX))
    {
        name = name.replace(DIRECTORYPREFIX, directoryPrefix);
    }
    if(name.contains(SIZELABEL))
    {
        name = name.replace(SIZELABEL, size->label());
    }
    if(name.contains(SIZEWIDTH))
    {
        name = name.replace(SIZEWIDTH, QString("%1").arg(size->width()));
    }
    if(name.contains(SIZEHEIGHT))
    {
        name = name.replace(SIZEHEIGHT, QString("%1").arg(size->height()));
    }
    if(name.contains(SIZESCALE))
    {
        name = name.replace(SIZESCALE, QString("%1").arg(size->scale()));
    }
    if(name.contains(RESOURCE_NAME))
    {
        name = name.replace(RESOURCE_NAME, resourceName);
    }
    return name;
}

QString SVGExportViewModel::buildResourceOutputFilePath(const QString &baseDirectory, const bool &useDirectoryWrapper,
                                                        const QString &wrapperDirectoryPattern, const QString &resourceNamePattern,
                                                        const Size * const size, const QString &directoryPrefix, const QString &resourceName)
{
    QChar separator = QDir::separator();
    QFileInfo baseInfo(baseDirectory);
    QString path = baseInfo.absoluteFilePath();
    if(useDirectoryWrapper)
    {
        QString wrapperName = buildName(wrapperDirectoryPattern, size, directoryPrefix, resourceName);
        path += separator + wrapperName;
    }
    QString fileName = buildName(resourceNamePattern, size, directoryPrefix, resourceName);
    path += separator + fileName;
    QFileInfo info(path);
    info.absoluteDir().mkpath(info.absoluteDir().absolutePath());
    return path;
}

void SVGExportViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
