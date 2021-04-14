#include <QtQml>
#include <QStandardPaths>

#include "applicationmanager.hpp"
#include "pathutils.hpp"
#include "xdatabase.hpp"
#include "exportdata.hpp"
#include "svgexportviewmodel.hpp"


ApplicationManager::ApplicationManager(QObject *parent)
    : MobileManager(parent)
{
}

void ApplicationManager::addContextProperty(QQmlEngine *engine, QQmlContext *context)
{
    m_engine = engine;

    //Register singletons
    qmlRegisterSingletonType(QUrl(QLatin1String("qrc:/qml/XMaterialControls.qml")), "XApps.XMaterialControls", 1, 0, "XMaterialControls");

    //Link C++ objects with QML
    context->setContextProperty("ApplicationManagerObj", this);
    context->setContextProperty("ApplicationSettingsObj", &m_applicationSettings);

    //Register image providers
    m_engine->addImageProvider("resources", &m_imageProvider);

    //Register data types
    qRegisterMetaType<Template>("Template");
    qRegisterMetaType<Size>("Size");
    qRegisterMetaType<ExportData>("ExportData");
    qRegisterMetaType<ExportData*>("ExportData*");
    qRegisterMetaType<QList<Template*>>("QList<Template*>");
    qRegisterMetaType<QList<Size*>>("QList<Size*>");
    qmlRegisterType<SVGExportViewModel>("XApps.SVGExportToMobileResources", 1, 0, "SVGExportViewModel");
    qmlRegisterType<ExportData>("XApps.SVGExportToMobileResources", 1, 0, "ExportData");
}

void ApplicationManager::initialize()
{
    m_databaseManager.initialize(m_applicationSettings.firstExecution());
    m_applicationSettings.setFirstExecution(false);
    m_applicationSettings.saveSettings();
}

void ApplicationManager::onAboutToQuit()
{
    m_applicationSettings.saveSettings();
}

void ApplicationManager::onApplicationStateChanged(Qt::ApplicationState applicationState)
{
    if(applicationState == Qt::ApplicationState::ApplicationSuspended)
        onAboutToQuit();
}
