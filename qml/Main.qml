import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import "qrc:/qml"
import "qrc:/qml/pages"

XApplication {
    id: appRoot
    visible: true
    width: 850
    minimumWidth: 850
    height: 650
    minimumHeight: 650
    title: qsTr("SVG Export to Mobile Resources")

    Material.theme: ApplicationSettingsObj.theme
    Material.primary: ApplicationSettingsObj.primaryColor
    Material.accent: ApplicationSettingsObj.accentColor

    onAppNavControllerCreated: {
        if(Qt.platform.os === "android" || Qt.platform.os === "ios") {
            ApplicationManagerObj.setUiReady(true)
        }
    }

    function initialization() {
        ApplicationManagerObj.initialize()
        appNavController.gotoView(appRoot.onHomePageIndex)
    }

    splashViewSourceComponent: SplashPage {}

    property int onHomePageIndex:   0
    viewNavigationModel: [
        { view: "pages/HomePage.qml",   stacked: false }
    ]
}
