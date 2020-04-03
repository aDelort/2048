import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: popup
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 200
    height: 200
    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Text {
        id: element
        x: 0
        text: qsTr("Taille de la grille")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 15
    }

    SpinBox {
        id: spinBox
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        to: 7
        from: 4
        value: 4
    }

    Button {
        id: cancelButton
        height: 35
        text: qsTr("Annuler")
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        onClicked: popup.close()
    }

    Button {
        id: okButton
        width: 40
        height: 35
        text: qsTr("OK")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 0
        onClicked: {
            vueObjectGame.setGridSize(spinBox.value);
            popup.close();
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_x:0;anchors_y:0}D{i:2;anchors_y:50}
}
##^##*/
