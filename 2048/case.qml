import QtQuick 2.0

Rectangle {
    id: rectangle
    width: 87
    height: 87
    property alias valueColor: value.color
    property alias valueText: value.text

    Text {
        id: value
        x: 32
        y: 36
        text: qsTr("")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 20
    }
}
