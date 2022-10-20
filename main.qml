import QtQuick 2.9
import QtQuick.Window 2.3


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("SiropWeather")

    Rectangle {
        id: backgroundRectangle
        x: 0
        y: 0
        width: 640
        height: 480

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#006d77" }
            GradientStop { position: 0.33; color: "#457b9d" }
            GradientStop { position: 0.9; color: "#83c5be" }
            GradientStop { position: 1.0; color: "#edf6f9" }
        }

        Image {
            id: weatherStatusImage
            x: 40
            y: 50
            width: 100
            height: 100
            source: "img/cloudy.png"
            antialiasing: false
            autoTransform: false
            mipmap: false
            mirror: false
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: weatherStatusText
            x: 170
            y: 50
            width: 180
            height: 50
            color: "#f1faee"
            text: "Облачно"
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.DemiBold
            font.family: "Monocraft"
            styleColor: "#edf6f9"
            textFormat: Text.RichText
        }

        Text {
            id: degreesText
            x: 170
            y: 106
            width: 180
            height: 44
            color: "#edf6f9"
            text: "+9°C"
            font.letterSpacing: 2
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Monocraft"
            styleColor: "#edf6f9"
            textFormat: Text.RichText
            font.styleName: "Обычный"
        }

        Text {
            id: text1
            x: 356
            y: 50
            width: 276
            height: 50
            color: "#f1faee"
            text: qsTr("Москва")
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            layer.smooth: false
            font.weight: Font.Medium
            font.family: "Monocraft"
        }
    }
}
