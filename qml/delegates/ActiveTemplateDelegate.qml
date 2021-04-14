import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import XApps.SVGExportToMobileResources

import "qrc:/qml"


XPane {
    id: delegate
    ToolTip.text: name

    function options() {
        var sizes = []
        for(var i = 0; i < sizeModel.count; i++) {
            sizes.push(lstSizes.itemAtIndex(i).checked)
        }
        exportData.options = sizes
        return exportData
    }

    ExportData {
        id: exportData
        useWrapperDirectory: modelData.useWrapperDirectory
        wrapperDirectoryNamePattern: modelData.wrapperDirectoryNamePattern
        resourceFileNamePattern: modelData.resourceFileNamePattern
    }

    ColumnLayout {
        id: delegateLayout
        anchors.fill: parent

        XSubheadingLabel {
            id: lblName
            text: name
            Layout.fillWidth: true
            width: delegateLayout.width
            wrapMode: Label.WrapAtWordBoundaryOrAnywhere
        }

        ListView {
            id: lstSizes
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 12
            cacheBuffer: 2000
            header: ColumnLayout {
                id: headerSizes
                width: lstSizes.width
                spacing: 8

                XCaptionLabel {
                    id: lblDescription
                    text: description
                    Layout.fillWidth: true
                    width: delegateLayout.width
                    wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                    color: Material.secondaryTextColor
                }

                GroupBox {
                    id: groupDirectoryWrapper
                    Layout.fillWidth: true

                    label: CheckBox {
                        id: chxWrapperDirectory
                        checked: useWrapperDirectory
                        text: qsTr("Use wrapper directory")
                        bottomPadding: 0
                        onCheckedChanged: exportData.useWrapperDirectory = checked
                    }

                    ColumnLayout {
                        anchors.fill: parent
                        enabled: chxWrapperDirectory.checked

                        XFormTextFieldFilled {
                            id: txfDirectoryPattern
                            Layout.fillWidth: true
                            placeholderText: qsTr("Directory name pattern")
                            text: wrapperDirectoryNamePattern
                            onTextChanged: exportData.wrapperDirectoryNamePattern = text
                        }
                        XFormTextFieldFilled {
                            id: txfDirectoryPrefix
                            Layout.fillWidth: true
                            placeholderText: qsTr("Prefix")
                            text: wrapperDirectoryPrefix
                            onTextChanged: exportData.directoryPrefix = text
                        }
                    }
                }

                XFormTextFieldFilled {
                    id: txfFilenamePattern
                    Layout.fillWidth: true
                    placeholderText: qsTr("Resource file name pattern")
                    text: resourceFileNamePattern
                    onTextChanged: exportData.resourceFileNamePattern = text
                }

                XFormTextFieldFilled {
                    id: txfResourceName
                    Layout.fillWidth: true
                    placeholderText: qsTr("Resource name")
                    text: viewModel.filename
                    onTextChanged: exportData.resourceName = text
                }

                Item {
                    height: 12
                }
            }
            clip: true
            ScrollIndicator.vertical: ScrollIndicator {}
            model: sizeModel
            delegate: XCheckDelegate {
                width: lstSizes.width
                topPadding: 2
                bottomPadding: 2
                spacing: 1
                text: label
                secondaryText: "x" + iconScale + "  (" + iconWidth + ", " + iconHeight + ")"
                ToolTip.text: label + (iconScale > 0 ? ("   x" + iconScale) : "" ) + "  (" + iconWidth + ", " + iconHeight + ")"
                ToolTip.visible: hovered
                ToolTip.delay: 1500
            }
        }
    }
}
