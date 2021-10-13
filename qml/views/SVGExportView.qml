import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts
import Qt.labs.platform

import XApps.SVGExportToMobileResources

import "qrc:/qml"
import "qrc:/qml/delegates"
import "qrc:/qml/listeners"


XPane {
    id: svgExportView
    title: qsTr("SVG Export View")

    Component.onCompleted: {
        viewModel.readTemplates()
    }

    SVGExportViewModel {
        id: viewModel
    }

    SVGExportViewListener {
        id: listener

        function update() {
            console.log("Update export view")
        }
    }

    FolderDialog {
        id: saveDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            txfOutputFolder.text = viewModel.cleanDirPath(folder)
        }
    }

    XPane {
        id: templatesSection
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 250
        Material.elevation: 2
        enabled: !viewModel.isWorking

        ColumnLayout {
            id: templatesSectionLayout
            anchors.fill: parent

            XSubheadingLabel {
                text: qsTr("Templates")
            }

            ListView {
                id: lstTemplates
                ScrollIndicator.vertical: ScrollIndicator {}
                Layout.fillHeight: true
                Layout.fillWidth: true
                clip: true
                delegate: TemplateDelegate {
                    width: lstTemplates.width
                    onCheckedChanged: {
                        if(checked) {
                            viewModel.addTemplate(index)
                        } else {
                            viewModel.removeTemplate(index)
                        }
                    }
                }
                model: viewModel.templateModel
            }
        }
    }

    ColumnLayout {
        id: vectorSectionLayout
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: templatesSection.left
        anchors.rightMargin: svgExportView.padding
        spacing: 12
        enabled: !viewModel.isWorking

        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            Image {
                id: imgOriginalVector
                sourceSize.width: 80
                sourceSize.height: 80
                cache: false
                source: "image://resources/" +
                        (viewModel.filepath.length > 0
                         ? viewModel.filepath
                         : (Material.theme === Material.Light
                            ? "defaultLight"
                            : "defaultDark"))
            }

            ColumnLayout {
                Layout.fillWidth: true

                XSubheadingLabel {
                    Layout.fillWidth: true
                    width: parent.width
                    text: viewModel.filename.length > 0
                          ? viewModel.filename
                          : qsTr("No svg resource loaded")
                }

                XCaptionLabel {
                    Layout.fillWidth: true
                    wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                    text: viewModel.filepath
                }
            }
        }

        XFormTextFieldFilled {
            id: txfOutputFolder
            Layout.fillWidth: true
            placeholderText: qsTr("Output directory")
            rightItemMargin: 4
            rightItem: ToolButton {
                icon.color: txfOutputFolder.enabled ? Material.accent : Material.hintTextColor
                icon.width: 24
                icon.height: 24
                icon.source: "qrc:/img/icons/folder-open.svg"
                display: IconLabel.IconOnly
                onClicked: {
                    saveDialog.open()
                }
            }
        }

        ListView {
            id: lstActiveTemplates
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: ListView.Horizontal
            model: viewModel.activeTemplateModel
            ScrollIndicator.horizontal: ScrollIndicator {}
            delegate: ActiveTemplateDelegate {
                height: lstActiveTemplates.height
                width: 350
            }
        }

        Button {
            text: qsTr("Export")
            highlighted: true
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                if(viewModel.filepath.length == 0) {
                    toastCtrl.showText(qsTr("Please choose an svg file"))
                } else if(txfOutputFolder.length == 0) {
                    toastCtrl.showText(qsTr("Please set the output directory"))
                } else {
                    var options = {}
                    for(var i = 0; i < viewModel.activeTemplateModel.count; i++) {
                        var templateItem = lstActiveTemplates.itemAtIndex(i)
                        var option = templateItem.options()
                        options[i] = option
                    }
                    viewModel.exportResources(txfOutputFolder.text, options)
                }
            }
        }
    }

    Rectangle {
        anchors.fill: dropArea
        color: Material.secondaryTextColor
        visible: opacity > 0
        opacity: dropArea.containsDrag
        Behavior on opacity { NumberAnimation {} }

        ColumnLayout {
            anchors.centerIn: parent

            IconLabel {
                icon.source: "qrc:/img/icons/target.svg"
                icon.width: 64
                icon.height: 64
                icon.color: Material.foreground
                Layout.alignment: Qt.AlignHCenter
                display: IconLabel.IconOnly
                Material.theme: Material.Dark
            }

            XBodyLabel1 {
                text: qsTr("Drop the file here")
                Layout.alignment: Qt.AlignHCenter
                Material.theme: Material.Dark
            }
        }
    }

    XPane {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 16
        radius: height / 2
        Material.elevation: 3
        padding: 2
        visible: opacity > 0
        opacity: viewModel.isWorking ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 100 } }

        BusyIndicator {
            anchors.centerIn: parent
            implicitWidth: 32
            implicitHeight: 32
        }
    }

    DropArea {
        id: dropArea
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: templatesSection.left
        anchors.rightMargin: svgExportView.padding
        enabled: !viewModel.isWorking

        onEntered: {
            if(drag.urls.length > 1) {
                toastCtrl.showText(qsTr("Please only drop one file at a time"))
                drag.accepted = false
                return false
            } else {
                if(!viewModel.isSVGFile(drag.urls[0])) {
                    toastCtrl.showText(qsTr("File is not an SVG"))
                    drag.accepted = false
                    return false
                } else {

                }
            }
        }

        onDropped: {
            console.log(drop.text)
            console.log(drop.urls)
            viewModel.loadSVG(drop.urls[0])
        }
    }

    XToast {
        id: toastCtrl
    }

}
