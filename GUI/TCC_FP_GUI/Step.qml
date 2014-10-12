import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    width: 660
    height: 225
    color: "#00000000"

    Text {
        id: text1
        x: 0
        y: 0
        width: 660
        height: 25
        color: "#ffffff"
        text: qsTr("Step Name")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
    }

    Rectangle {
        id: rectangle1
        x: 218
        y: 25
        width: 4
        height: 175
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        border.width: 0
    }

    Rectangle {
        id: rectangle2
        x: 438
        y: 25
        width: 4
        height: 175
        border.width: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
    }

    Image {
        id: image1
        x: 49
        y: 40
        width: 120
        height: 150
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Image {
        id: image2
        x: 269
        y: 40
        width: 120
        height: 150
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Image {
        id: image3
        x: 489
        y: 40
        width: 120
        height: 150
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Button {
        id: button1
        x: 155
        y: 200
        width: 350
        height: 25
        text: qsTr("Próxima etapa")
    }
}
