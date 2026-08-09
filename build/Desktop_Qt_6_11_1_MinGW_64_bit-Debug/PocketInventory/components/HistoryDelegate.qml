import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: root

    required property string productName
    required property int oldQuantity
    required property int newQuantity
    required property string action
    required property string createdAt

    implicitHeight: 100
    radius: 8

    color: "#f5f5f5"

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 12
        spacing: 5

        RowLayout{
            Layout.fillWidth:  true

            Label{
                text: root.productName
                font.pixelSize: 16
                font.bold: true

                Layout.fillWidth: true
            }

            Label{
                text: root.actionText(root.action)
                font.bold: true
                color: actionColor(root.action)
            }

            Label{
                text:
                root.oldQuantity + "개 ->" + root.newQuantity + "개"
                font.pixelSize: 15
            }

            Label {
                text: root.createdAt
                color: "gray"
                font.pixelSize: 12
            }
        }
    }

    function actionColor(action){
        switch(action){
        case "PURCHASE":
            return "blue"

        case "SALE":
            return "darkorange"

        case "CREATE":
            return "green"

        case "INCREASE":
            return "blue"

        case "DECREASE":
            return "darkorange"

        case "DELETE":
            return "red"

        default:
            return "gray"
        }
    }

    function actionText(action) {
        switch (action) {
        case "CREATE":
            return "등록"

        case "INCREASE":
            return "증가"

        case "DECREASE":
            return "감소"

        case "PURCHASE":
            return "입고"

        case "SALE":
            return "출고"

        case "DELETE":
            return "삭제"

        default:
            return action
        }
    }
}
