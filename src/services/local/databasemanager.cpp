#include <QStandardPaths>

#include "databasemanager.hpp"
#include "pathutils.hpp"
#include "template.hpp"
#include "size.hpp"
#include "constants.hpp"


DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{    
    m_database = nullptr;
}

DatabaseManager::~DatabaseManager()
{
    if(m_database != nullptr) {
        if(m_database->isOpen()) {
            m_database->close();
        }

        m_database->deleteLater();
    }
}

void DatabaseManager::initialize(const bool &populate)
{
    m_databaseFilePath = PathUtils::appicationDataPath() + PathUtils::SEPARATOR + DATABASE_FILE_NAME;
    PathUtils::makeParentPath(m_databaseFilePath);
    m_database = new XDatabase(m_databaseFilePath, DATABASE_CONNECTION_NAME, EMPTY_TEMPLATE);
    bool opened = m_database->open();
    if(opened) {
        QSqlError error;
        error = m_database->registerModel<Template>();
        if(error.isValid()) qWarning("%s", error.text().toLocal8Bit().data());
        error = m_database->registerModel<Size>();
        if(error.isValid()) qWarning("%s", error.text().toLocal8Bit().data());

        if(populate)
        {
            XDao<Template> templateDao;
            templateDao.setDatabase(*m_database->database());
            XDao<Size> sizeDao;
            sizeDao.setDatabase(*m_database->database());

            Template* templatee = new Template("Android Icon Launcher");
            templatee->setDescription("Icon launcher must be scaled using a base dimension of 48x48 equivalent to mdpi");
            templatee->setUseWrapperDirectory(true);
            templatee->setWrapperDirectoryNamePattern(QString("%1-%2").arg(DIRECTORYPREFIX).arg(SIZELABEL));
            templatee->setWrapperDirectoryPrefix("mipmap");
            templatee->setResourceFileNamePattern(QString("%1.png").arg(RESOURCE_NAME));
            templateDao.createOne(templatee);

            Size* size = nullptr;
            size = new Size("ldpi", 0.5, 24, 24, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("mdpi", 1.0, 48, 48, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("hdpi", 1.5, 72, 72, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("xhdpi", 2.0, 96, 96, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("xxhdpi", 3.0, 144, 144, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("xxxhdpi", 4.0, 192, 192, templatee->guid());
            sizeDao.createOne(size);
            size = new Size("Web", 10.67, 512, 512, templatee->guid());
            sizeDao.createOne(size);
        }
    }
}
