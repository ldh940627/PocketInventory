import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{

    property string title: ""
    property string value: ""

    property color cardColor: "#ffffff"
    property color valueColor: "black"

    radius: 8

    color: cardColor

    Layout.fillWidth: true
    Layout.preferredHeight: 80

    ColumnLayout{
        anchors.centerIn: parent
        spacing: 2

        Label{
            text: title
            font.pixelSize: 12
            color: "#555555"

            Layout.alignment: Qt.AlignHCenter
        }

        Label{
            text: value
            font.pixelSize: 20
            font.bold: true
            color: valueColor

            Layout.alignment: Qt.AlignHCenter
        }
    }
}
