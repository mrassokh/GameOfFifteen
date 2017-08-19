import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 400
    height: 480
    title: qsTr("Amazing Game")
    minimumWidth: 150
    minimumHeight: 230

    BoardContainer{
         id: squareBoard
    }

    Button {
         id: mixButton
         text: qsTr("Mix squares!")
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.top: squareBoard.bottom
         anchors.topMargin: 10
         anchors.leftMargin: 10
         anchors.rightMargin: 10

         onClicked: {
                logic.refresh();
                squareBoard.updateGameBoard();
         }
    }

    Button {
         id: exit
         text: qsTr("Exit")
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.top: mixButton.bottom
         anchors.topMargin: 10
         anchors.leftMargin: 10
         anchors.rightMargin: 10

         onClicked: {
             squareBoard.destroyGameBoard();
             Qt.quit();
         }
    }

    WinnerWindow{
         id: winnerWindow
    }

    Component.onCompleted: {
           setX(Screen.width / 2 - width / 2);
           setY(Screen.height / 2 - height / 2);
    }
}
