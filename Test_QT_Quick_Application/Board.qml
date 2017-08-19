import QtQuick 2.0

Item {

    width: parent.width
    height: parent.height - 80

    property int squareSizeX: (width - 5) / 4
    property int squareSizeY: (height - 5) /4

    Rectangle {
        width: parent.width
        height: parent.height
        color: "black"

     Repeater {
         model: logic

         Rectangle {
             width: squareSizeX - 5; height: squareSizeY - 5
             x: squareSizeX * positionX + 6
             y: squareSizeY *positionY + 6
             color: "lightgreen"

             Behavior on x { PropertyAnimation { duration: 300 } }
             Behavior on y { PropertyAnimation { duration: 300 } }


             function fontSize(){
                 var size = Math.min(squareSizeX / 2, squareSizeY / 2);
                 return size;
              }

              Text {
                  text: number
                  font.pointSize: fontSize()
                  anchors.centerIn: parent
              }

              MouseArea {
                  anchors.fill: parent
                  drag.target: parent

                  property int startX: 0
                  property int startY: 0

                  onPressed: {
                      startX = parent.x
                      startY = parent.y
                  }

                  onReleased: {
                      var fromX = startX / squareSizeX
                      var fromY = startY / squareSizeY
                      var toX   = (parent.x + mouseX) /squareSizeX
                      var toY   = (parent.y + mouseY) / squareSizeY

                      logic.move(fromX, fromY, toX, toY)
                      parent.x =  squareSizeX * positionX + 6;
                      parent.y =  squareSizeY * positionY + 6;

                      if (logic.checkWin()){
                          winnerWindow.setX(mainWindow.x)
                          winnerWindow.setY(mainWindow.y + mainWindow.height/2 -  winnerWindow.height/2)
                          winnerWindow.show()
                      }
                   }

                   onClicked: {
                       logic.findEmpty();

                       var fromX = parent.x / squareSizeX
                       var fromY = parent.y / squareSizeY
                       var toX   =  logic.getEmptyX();
                       var toY   = logic.getEmptyY();

                       logic.move(fromX, fromY, toX, toY);
                       parent.x =  squareSizeX * positionX + 6;
                       parent.y =  squareSizeY * positionY + 6;
                       if (logic.checkWin()){
                            winnerWindow.setX(mainWindow.x)
                            winnerWindow.setY(mainWindow.y + mainWindow.height/2 -  winnerWindow.height/2)
                            winnerWindow.show()
                       }
                  }
             }
        }

    }
  }
}
