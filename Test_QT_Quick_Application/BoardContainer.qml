import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Item {
    x: 0
    y: 0
    width : parent.width
    height:  parent.height - 80

    property var gameBoard: createGameBoard()

    function createGameBoard(){
        var BoardComponent = Qt.createComponent("Board.qml");
        var BoardObject = BoardComponent.createObject(parent);
        if (BoardObject === null) {
               console.log("Error creating BoardObject");
         }        
        return BoardObject;
    }

    function updateGameBoard() {
        var tmp = gameBoard;
        gameBoard = createGameBoard();
        tmp.destroy();
    }

    function destroyGameBoard() {
        gameBoard.destroy();
    }

    onWidthChanged: {
        updateGameBoard()
    }

    onHeightChanged: {
        updateGameBoard()
    }

}
