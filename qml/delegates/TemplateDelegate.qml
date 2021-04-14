import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

import "qrc:/qml"


XSwitchDelegate {
    id: delegate

    text: name
    ToolTip.text: name
    ToolTip.visible: hovered
    ToolTip.delay: 1500

    indicator: SwitchIndicator {
        x: delegate.text ? (delegate.mirrored ? delegate.leftPadding : delegate.width - width - delegate.rightPadding) : delegate.leftPadding + (delegate.availableWidth - width) / 2
        y: delegate.topPadding + (delegate.availableHeight - height) / 2
        control: delegate
    }

//    swipe.right: deleteComponent
//    swipe.onCompleted: {
//        viewModel.deleteMember(guid, index)
//    }
//    Component {
//        id: deleteComponent

//        Rectangle {
//            id: editContainer
//            width: parent.width
//            height: parent.height
//            color: Material.color(Material.Red)
//            visible: swipe.position !== 0

//            IconLabel {
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.right: parent.right
//                anchors.rightMargin: 20
//                icon.source: "qrc:/img/icons/delete.svg"
//                icon.width: 32
//                icon.height: 32
//                icon.color: "#FFFFFF"
//            }
//        }
//    }

//    ListView.onRemove: SequentialAnimation {
//        PropertyAction {
//            target: delegate
//            property: "ListView.delayRemove"
//            value: true
//        }
//        NumberAnimation {
//            target: delegate
//            property: "height"
//            to: 0
//            easing.type: Easing.InOutQuad
//        }
//        PropertyAction {
//            target: delegate
//            property: "ListView.delayRemove"
//            value: false
//        }
//    }

//    onClicked: {
//        homeNavController.gotoView(homeNavController.memberDetailsViewIndex, guid)
//    }
}
