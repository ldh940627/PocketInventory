import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property int index

    required property string productName
    required property int oldQuantity
    required property int newQuantity
    required property string action
    required property string createdAt

    AppTheme {
        id: theme
    }

    implicitHeight: 56
    color: "transparent"

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4

        spacing: 12

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Label {
                text: root.productName

                color: theme.textPrimary

                font.pixelSize: 14
                font.bold: true
            }

            Label {
                text: root.createdAt

                color: theme.textSecondary
                font.pixelSize: 11
            }
        }

        Label {
            text:
                root.oldQuantity
                + " → "
                + root.newQuantity

            color: theme.textPrimary
            font.bold: true
        }

        Rectangle {
            implicitWidth: 76
            implicitHeight: 26

            radius: 13

            color: actionBackground(root.action)

            Label {
                anchors.centerIn: parent

                text: actionText(root.action)

                color: actionColor(root.action)

                font.pixelSize: 11
                font.bold: true
            }
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

    function actionColor(action) {
        switch (action) {
        case "CREATE":
        case "INCREASE":
        case "PURCHASE":
            return theme.success

        case "DECREASE":
        case "SALE":
            return theme.warning

        case "DELETE":
            return theme.danger

        default:
            return theme.textSecondary
        }
    }

    function actionBackground(action) {
        switch (action) {
        case "CREATE":
        case "INCREASE":
        case "PURCHASE":
            return theme.successSoft

        case "DECREASE":
        case "SALE":
            return theme.warningSoft

        case "DELETE":
            return theme.dangerSoft

        default:
            return "#F3F4F6"
        }
    }
}