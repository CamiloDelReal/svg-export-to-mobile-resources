import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import "qrc:/qml"
import "qrc:/qml/dialogs"
import "qrc:/qml/views"

XTitledPage {
    id: homePage
    statusbarHeight: ApplicationManagerObj.systemStatusBarSize

    titlebar.title: qsTr("SVG Export")
    titlebar.subtitle: qsTr("to Mobile Resources")

    titlebar.menuActions: [
        XAction {
            text: qsTr("Options")
            icon.source: "qrc:/img/icons/tune.svg"
            onTriggered: {
                showOptionsColorDialog()
            }
        }
    ]

    function back() {
        if(homeNavController.depth > 1) {
            homeNavController.goBack()
            return true
        }
        return false
    }

    Loader {
        id: optionsDialogLoader
        active: false
        visible: false
        sourceComponent: OptionsDialog {
            onClosed: {
                optionsDialogLoader.active = false
            }
        }
        onLoaded: {
            item.open()
        }
    }

    function showOptionsColorDialog() {
        optionsDialogLoader.active = true
    }

    XViewNavController {
        id: homeNavController
        anchors.fill: parent

        initialView: SVGExportView {}

        property int templateEditionViewIndex: 0
        viewNavigationModel: [
            { view: "views/TemplateEditionView.qml", stacked: true },
        ]
    }
}
