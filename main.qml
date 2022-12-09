import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 1.4
import QtQuick.Controls 2.14
import QtCharts 2.14

Window {
    visible: true
    title: "Stack Overflow Stats"
    width: 855
    height: 410
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

    Calendar {
        id: calendar
        objectName: "calendar"
        x: 15
        y: 55
        width: 260
        height: 260
    }

    Button {
        id: buttonPrevYear
        x: 15
        y: 15
        width: 125
        height: 30
        text: "<<"
        onClicked: calendar.showPreviousYear()
    }

    Button {
        id: buttonNextYear
        x: 150
        y: 15
        width: 125
        height: 30
        text: ">>"
        onClicked: calendar.showNextYear()
    }

    ChartView {
        id: chartView
        objectName: "chartView"
        x: 285
        y: 15
        width: 555
        height: 340
        legend.visible: false
        antialiasing: true

        margins.left: 0
        margins.right: 0
        margins.top: 0
        margins.bottom: 0

        LineSeries {
            id: chartSeries
            axisX: ValueAxis{}
            axisY: ValueAxis{}
        }
    }

    ComboBox {
        id: comboBoxPeriod
        objectName: "comboBoxPeriod"
        x: 15
        y: 325
        width: 135
        height: 30
        textRole: "text"
        valueRole: "value"

        model: [
            {value: Qt.point(7,1), text: "Неделя"},
            {value: Qt.point(4,7), text: "Месяц"},
            {value: Qt.point(9,10), text: "Три месяца"},
            {value: Qt.point(6,30), text: "Полгода"}
        ]
    }

    ComboBox {
        id: comboBoxTag
        objectName: "comboBoxTag"
        x: 160
        y: 325
        width: 115
        height: 30

        model: ["Qt", "Desktop", "cpp"]
    }

    Button {
        id: buttonSend
        x: 15
        y: 365
        width: 260
        height: 30
        text: "Отправить"
        onClicked: appEngine.buttonSend_onClick()
    }

    Label {
        id: labelDateInterval
        objectName: "labelDateInterval"
        x: 285
        y: 365
        width: 555
        height: 30
        horizontalAlignment: "AlignHCenter"
        verticalAlignment: "AlignVCenter"

        font.pixelSize: 16
    }
}
