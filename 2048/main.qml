import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id: window
    visible: true
    width: (10 + 87)*vueObjectGame.gridSize + 10 + 30;
    height: (10 + 87)*vueObjectGame.gridSize + 10 + 230;
    color: "#faf8ef"
    title: qsTr("2048")

    Rectangle {
        id: headerRect
        x: 0
        width: (10 + 87)*vueObjectGame.gridSize + 10
        height: 100
        color: "#00000000"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: currentScoreRect
            x: 0
            y: 0
            width: 100
            height: 80
            color: "#bbada0"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 10

            Text {
                id: element
                color: "#eee4da"
                text: qsTr("Score")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 5
                font.pixelSize: 20
            }

            Text {
                id: scoreLabel
                x: 23
                color: "#ffffff"
                text: vueObjetScoreCnt.cntQML
                anchors.top: parent.top
                anchors.topMargin: 35
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: bestScoreRect
            x: 0
            width: 100
            height: 80
            color: "#bbada0"
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 110

            Text {
                id: element1
                x: -151
                y: 0
                color: "#eee4da"
                text: qsTr("Best")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                font.pixelSize: 20
                anchors.topMargin: 5
            }

            Text {
                id: bestScoreLabel
                x: 23
                color: "#ffffff"
                text: vueObjetBestScoreCnt.cntQML
                anchors.topMargin: 35
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: optionsButton
            width: 100
            height: 80
            color: "#8F7A66"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

            Text {
                id: element5
                color: "#eee4da"
                text: qsTr("Options")
                verticalAlignment: Text.AlignVCenter
                anchors.topMargin: 0
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
            }

            MouseArea {
                id: mouseArea4
                anchors.fill: parent
                onClicked: optionsPopup.open()
            }
        }

        OptionsPopup {
            id: optionsPopup4
        }
    }

    Rectangle {
        id: gameRect
        x: 0
        width: (10 + 87)*vueObjectGame.gridSize + 10;
        height: (10 + 87)*vueObjectGame.gridSize + 10;
        color: "#bbada0"
        anchors.top: parent.top
        anchors.topMargin: 140
        anchors.horizontalCenter: parent.horizontalCenter
        focus: true
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up:
                vueObjectGame.moveTop();
                break;
            case Qt.Key_Down:
                vueObjectGame.moveDown();
                break;
            case Qt.Key_Left:
                vueObjectGame.moveLeft();
                break;
            case Qt.Key_Right:
                vueObjectGame.moveRight();
                break;
            }
        }

        Grid {
            id: grid
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            spacing: 10
            transformOrigin: Item.TopLeft
            anchors.fill: parent
            rows: vueObjectGame.gridSize;
            columns: vueObjectGame.gridSize;
            objectName: "damier"
        }
    }

    Rectangle {
        id: footerRect
        x: -4
        y: 0
        width: (10 + 87)*vueObjectGame.gridSize + 10
        height: 50
        color: "#00000000"
        anchors.top: parent.top
        anchors.topMargin: 140 + (10 + 87)*vueObjectGame.gridSize + 10 + 20;
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: restartButton
            width: 100
            height: 40
            color: "#8F7A66"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: element2
                color: "#eee4da"
                text: qsTr("Restart")
                anchors.topMargin: 7
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: vueObjectGame.restart()
            }
        }

        Rectangle {
            id: undoButton
            width: 80
            height: 40
            color: "#8F7A66"
            visible: !vueObjectGame.isBeginHistory
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: element3
                color: "#eee4da"
                text: qsTr("Undo")
                anchors.topMargin: 7
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
            }

            MouseArea {
                id: mouseArea2
                anchors.fill: parent
                onClicked: vueObjectGame.undo()
            }
        }

        Rectangle {
            id: redoButton
            x: 2
            y: 1
            width: 80
            height: 40
            color: "#8F7A66"
            visible: !vueObjectGame.isEndHistory
            anchors.left: parent.left
            anchors.leftMargin: 90
            Text {
                id: element4
                color: "#eee4da"
                text: qsTr("Redo")
                anchors.topMargin: 7
                anchors.fill: parent
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: mouseArea3
                anchors.fill: parent
                onClicked: vueObjectGame.redo()
            }
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    OptionsPopup {
        id: optionsPopup
        onClosed: gameRect.focus = true
    }
}

/*##^##
Designer {
    D{i:4;anchors_height:200;anchors_width:150;anchors_y:0;invisible:true}D{i:2;anchors_height:200;anchors_width:200}
D{i:6;anchors_height:400;anchors_y:0}D{i:7;anchors_height:100;anchors_y:0;invisible:true}
D{i:9;anchors_height:400;anchors_width:400}D{i:10;anchors_height:80;anchors_width:80}
D{i:1;anchors_y:0}D{i:12;anchors_height:80;anchors_width:80}D{i:11;anchors_height:80;anchors_width:80}
D{i:13;anchors_height:80;anchors_width:80}
}
##^##*/
