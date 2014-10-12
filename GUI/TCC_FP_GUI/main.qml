import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 660
    height: 800
    color: "#000000"
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Image {
        id: image1
        x: 500
        y: 15
        width: 120
        height: 150
        source: "/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2000/DB2/101_1.jpg"
    }

    Button {
        id: button1
        x: 470
        y: 170
        width: 180
        text: qsTr("Selecione uma imagem")
    }

    Step {
        id: step1
        x: 0
        y: 243
    }

    Step {
        id: step2
        x: 0
        y: 492
    }
}
