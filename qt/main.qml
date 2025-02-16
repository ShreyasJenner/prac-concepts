import QtQuick 6.0
import QtQuick.Controls 6.0

function createRoundedBox(text, width, height, color, radius) {
    var rect = Rectangle {
        width: width
        height: height
        color: color
        radius: radius

        Text {
            anchors.centerIn: parent
            text: text
            font.pointSize: 20
        }
      }
      return rect
}

ApplicationWindow {
    visible: true
    width: 300
    height: 200

    // Define the function to create a rounded box with text
    

    // Create a rounded box using the function
    Rectangle {
        width: 300
        height: 200

        // Call the function to create the rounded box
        Component.onCompleted: {
            var box = createRoundedBox("Hello, World!", 200, 100, "lightblue", 20)
            box.x = 50
            box.y = 50
            parentItem.addChild(box)  // Adds the box to the parent
        }
    }
}

