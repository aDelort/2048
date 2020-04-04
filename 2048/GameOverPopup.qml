import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: endGamePopup
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 200
    height: 120
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Connections {
        target: vueObjectGame
        onGameOver: endGamePopup.open()
    }

    Text {
        id: element
        x: 0
        text: qsTr("Game over")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 20
    }

    Button {
        id: okButton
        width: 100
        height: 35
        text: qsTr("OK")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        onClicked: {
            endGamePopup.close();
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_x:0;anchors_y:0}D{i:2;anchors_y:50}
}
##^##*/
