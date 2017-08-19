import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.3


ApplicationWindow {
    title: qsTr("Congratulation!!!")
    color: "orchid"
    visible: false
    width: 400
    height: 80

    Rectangle{
        id: winnerText
        color: "bisque"
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Text{
            text:"You are the winner!!!"
            anchors.centerIn: parent
            font.pointSize: 30
            color: "orchid"
        }
    }

    Button{
        id: newGame
        text: qsTr("New Game")
        width: 150
        anchors.left: parent.left
        anchors.top:  winnerText.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 25
        anchors.rightMargin: 25

        onClicked: {
            logic.refresh();
            squareBoard.updateGameBoard();
            winnerWindow.hide();
        }
    }

    Button{
        id: exitGame
        text: qsTr("Exit")
        width: 150
        anchors.left: newGame.right
        anchors.top:  winnerText.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 50
        anchors.rightMargin: 25

        onClicked: {
            squareBoard.destroyGameBoard();
            Qt.quit();
        }
    }
}
