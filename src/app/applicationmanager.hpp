#ifndef APPLICATIONMANAGER_HPP
#define APPLICATIONMANAGER_HPP

#include <QObject>
#include <QQmlContext>

#include "applicationsettings.hpp"
#include "mobilemanager.hpp"
#include "databasemanager.hpp"
#include "imageprovider.hpp"


class ApplicationManager : public MobileManager
{
public:
    explicit ApplicationManager(QObject *parent = nullptr);

    void addContextProperty(QQmlEngine *engine, QQmlContext *context) override;

    Q_INVOKABLE void initialize() override;

public slots:
    void onAboutToQuit() override;
    void onApplicationStateChanged(Qt::ApplicationState applicationState) override;

private:
    QQmlEngine *m_engine;
    ApplicationSettings m_applicationSettings;
    DatabaseManager m_databaseManager;
    ImageProvider m_imageProvider;
};

#endif // APPLICATIONMANAGER_HPP
