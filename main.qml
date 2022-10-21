import QtQuick 2.9
import QtQuick.Window 2.3


Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("SiropWeather")

    maximumWidth: width
    minimumWidth: width

    maximumHeight: height
    minimumHeight: height


    Rectangle {
        id: backgroundRectangle
        x: 0
        y: 0
        width: 640
        height: 480
        color: "#f1faee"

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
            source: "qrc:/img/%1.png".arg(weatherData.weatherImagePath)  // .arg(weatherData.currentWeatherStatus)
            antialiasing: false
            autoTransform: false
            mipmap: false
            mirror: false
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: weatherStatusText
            x: 140
            y: 50
            width: 180
            height: 50
            color: "#f1faee"
            text: weatherData.currentWeatherStatus
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.DemiBold
            font.family: "Monocraft"
            styleColor: "#edf6f9"
            textFormat: Text.RichText
        }

        Text {
            id: degreesText
            x: 140
            y: 106
            width: 180
            height: 44
            color: "#edf6f9"
            text: "+%1°C".arg(weatherData.currentDegrees)
            font.letterSpacing: 2
            font.pixelSize: 26
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Monocraft"
            styleColor: "#edf6f9"
            textFormat: Text.RichText
            font.styleName: "Обычный"
        }

        Text {
            id: cityText
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

        Image {
            id: hygrometerImage
            x: 40
            y: 190
            width: 100
            height: 100
            source: "img/hygrometer.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: humidityText
            x: 170
            y: 190
            width: 120
            height: 40
            color: "#f1faee"
            text: qsTr("Влажность")
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Monocraft"
        }

        Text {
            id: humidityValue
            x: 170
            y: 236
            width: 125
            height: 40
            color: "#f1faee"
            text: qsTr("%1%".arg(weatherData.currentHumidity))
            font.letterSpacing: 2
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            antialiasing: true
            leftPadding: 0
            font.family: "Monocraft"
        }

        Image {
            id: windsockImage
            x: 301
            y: 190
            width: 100
            height: 100
            source: "img/windsock.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: windText
            x: 410
            y: 190
            width: 150
            height: 40
            color: "#f1faee"
            text: qsTr("Ветер")
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Monocraft"
        }

        Text {
            id: windValue
            x: 410
            y: 270
            width: 150
            height: 20
            color: "#f1faee"
            text: qsTr("%1м/с".arg(weatherData.currentWindSpeed))
            font.letterSpacing: 2
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            leftPadding: 0
            font.family: "Monocraft"
            antialiasing: true
        }

        Text {
            id: windDirection
            x: 410
            y: 230
            width: 150
            height: 34
            color: "#f1faee"
            text: qsTr(weatherData.currentWindDirection)
            font.letterSpacing: 2
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            leftPadding: 0
            font.family: "Monocraft"
            antialiasing: true
        }
    }
}
