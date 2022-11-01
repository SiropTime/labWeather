import QtQuick 2.9
import QtQuick.Window 2.3
import QtCharts 2.3
import QtQuick.Controls 2.3

Window {
    id: chartWindow
    width: 800; height: 300;

    maximumWidth: width
    minimumWidth: width

    maximumHeight: height
    minimumHeight: height



    Text {
        id: mainLabel
        x: 250
        y: 0
        width: 300
        height: 30

        text: qsTr("График изменения погоды")
        font.pixelSize: 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Monocraft"
    }

    ChartView {
        id: lineWeather
        animationOptions: ChartView.SeriesAnimations

        margins.left: 10
        margins.right: 10
        margins.top: 10
        margins.bottom: 10


        legend.font.family: "Monocraft"

        x: 0
        y: 50
        width: 800
        height: 250

        ValueAxis {
            id: _axisX
            max: 137
            min: 135
            labelsFont.family: "Monocraft"
        }

        ValueAxis {
            id: _axisY
            max: 40
            min: -40
            labelsFont.family: "Monocraft"
        }

        LineSeries {
            id: _xySeries;
            name: "Температура по времени"
            axisX: _axisX
            axisY: _axisY
            width: 4.0
            color: "#006d77"
        }


    }

    Component.onCompleted: {

        let models = dataBase.getDataForChart()
        for (var i = 0; i < models.length; i += 2) {
            var time = models[i]
            var temperature = models[i + 1]
            if (i ==  0) {
                _axisX.min = time
                _axisY.min = temperature - 5
            } else if (i ==  models.length - 2) {
                _axisX.max = time
                _axisY.max = temperature + 5
            }

            _xySeries.append(time, temperature);
        }
    }


}




