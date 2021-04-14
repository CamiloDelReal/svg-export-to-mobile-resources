#************  Qt Configurations  *****************************************************************
QT += qml quick quickcontrols2 svg xml
CONFIG += c++11 #qtquickcompiler
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


#************  X 3rd Party Libs  ******************************************************************


#************  X Modules  *************************************************************************
include($$PWD/../x_material_controls/x_material_controls.pri)
include($$PWD/../x_orm/x_orm.pri)
include($$PWD/../x_utils/x_utils.pri)


#************  QML Configurations  ****************************************************************
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH =


#************  App Sources  ***********************************************************************
HEADERS += \
    $$PWD/src/app/applicationmanager.hpp \
    $$PWD/src/app/applicationsettings.hpp \
    $$PWD/src/app/imageprovider.hpp \
    $$PWD/src/models/activetemplatemodel.hpp \
    $$PWD/src/models/sizemodel.hpp \
    $$PWD/src/models/templatemodel.hpp \
    $$PWD/src/services/entities/size.hpp \
    $$PWD/src/services/entities/template.hpp \
    $$PWD/src/services/local/databasemanager.hpp \
    $$PWD/src/utils/constants.hpp \
    $$PWD/src/viewmodels/svgexportviewmodel.hpp \
    src/services/entities/exportdata.hpp

SOURCES += \
    $$PWD/src/app/main.cpp \
    $$PWD/src/app/applicationmanager.cpp \
    $$PWD/src/app/applicationsettings.cpp \
    $$PWD/src/app/imageprovider.cpp \
    $$PWD/src/models/activetemplatemodel.cpp \
    $$PWD/src/models/sizemodel.cpp \
    $$PWD/src/models/templatemodel.cpp \
    $$PWD/src/services/entities/size.cpp \
    $$PWD/src/services/entities/template.cpp \
    $$PWD/src/services/local/databasemanager.cpp \
    $$PWD/src/viewmodels/svgexportviewmodel.cpp \
    src/services/entities/exportdata.cpp

INCLUDEPATH += \
    $$PWD/src/app \
    $$PWD/src/models \
    $$PWD/src/services/entities \
    $$PWD/src/services/local \
    $$PWD/src/services/remote \
    $$PWD/src/utils \
    $$PWD/src/viewmodels


#************  Resources  *************************************************************************
RESOURCES += \
    $$PWD/resources.qrc


#************  Images Files  **********************************************************************
DISTFILES +=  \
    $$PWD/img/app/logo.svg \
    $$PWD/img/app/logo_foreground.svg \
    $$PWD/img/icons/arrow-left.svg \
    $$PWD/img/icons/check.svg \
    $$PWD/img/icons/folder-open.svg \
    $$PWD/img/icons/target.svg \
    $$PWD/img/icons/tune.svg


#************  QML Files  *************************************************************************
DISTFILES += \
    $$PWD/qml/Main.qml \
    $$PWD/qml/delegates/ActiveTemplateDelegate.qml \
    $$PWD/qml/delegates/TemplateDelegate.qml \
    $$PWD/qml/dialogs/OptionsDialog.qml \
    $$PWD/qml/listeners/SVGExportViewListener.qml \
    $$PWD/qml/pages/SplashPage.qml \
    $$PWD/qml/pages/HomePage.qml \
    $$PWD/qml/views/SVGExportView.qml \
    $$PWD/qml/views/TemplateEditionView.qml


#************  Windows Deploy Configs  ************************************************************
win32* {
    RC_FILE = deploy/windows/manifest.rc
    #TARGET = "SVG Export to Mobile Resources"
}
