import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 430
    height: 630
    title: qsTr("Hello World")

    Rectangle {
        id: headerRect
        x: 0
        width: 400
        height: 100
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: currentScoreRect
            x: 0
            y: 0
            width: 150
            height: 80
            color: "#ffffff"
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.top: parent.top
            anchors.topMargin: 10

            Text {
                id: element
                text: qsTr("Score :")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: bestScoreRect
            x: 0
            width: 150
            height: 80
            color: "#ffffff"
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 25

            Text {
                id: element1
                x: -151
                y: 0
                text: qsTr("Best :")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                font.pixelSize: 20
                anchors.topMargin: 0
            }
        }
    }

    Rectangle {
        id: gameRect
        x: 0
        width: 400
        height: 400
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: 140
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: footerRect
        x: -4
        y: 0
        width: 400
        height: 50
        color: "#808080"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: restartButton
            width: 120
            height: 40
            color: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: element2
                text: qsTr("New Game")
                anchors.topMargin: 7
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
            }
        }
    }




}

/*##^##
Designer {
    D{i:2;anchors_height:200;anchors_width:200}D{i:4;anchors_height:200;anchors_width:150;anchors_y:0}
D{i:1;anchors_y:0}D{i:6;anchors_height:400;anchors_y:0}D{i:7;anchors_height:100;anchors_y:0}
}
##^##*/
