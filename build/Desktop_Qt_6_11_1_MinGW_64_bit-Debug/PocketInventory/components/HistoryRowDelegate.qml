import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property string productName
    required property int oldQuantity
    required property int newQuantity
    required property string action
    required property string details
    required property string createdAt

    AppTheme {
        id: theme
    }

    implicitHeight: 62

    color:
        mouseArea.containsMouse ? theme.surfaceSoft : "transparent"

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 20
        anchors.rightMargin: 20

        spacing: 12

        Label {
            text: root.productName

            Layout.fillWidth: true
            Layout.preferredWidth: 4

            color: theme.textPrimary

            font.pixelSize: 14
            font.bold: true

            elide: Text.ElideRight
        }

        Label {
            text: root.action === "EDIT" ? root.details : root.oldQuantity + "개 → " + root.newQuantity + "개"

            Layout.preferredWidth: 170

            color: theme.textPrimary
            font.pixelSize: 13

            horizontalAlignment: root.action === "EDIT" ? Text.AlignLeft : Text.AlignHCenter

            elide: Text.ElideRight
        }

        Item {
            Layout.preferredWidth: 110
            Layout.preferredHeight: 28

            Rectangle {
                anchors.centerIn: parent

                width: 72
                height: 24

                radius: 6

                color:
                    actionBackground(root.action)

                Label {
                    anchors.centerIn: parent

                    text:
                        actionText(root.action)

                    color:
                        actionColor(root.action)

                    font.pixelSize: 11
                    font.bold: true
                }
            }
        }

        Label {
            text:
                root.formatDate(root.createdAt)

            Layout.preferredWidth: 130

            color: theme.textSecondary
            font.pixelSize: 12

            horizontalAlignment: Text.AlignHCenter
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        acceptedButtons: Qt.NoButton
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 1

        color: theme.border
    }

    function formatDate(dateText) {
            const date = new Date(
                dateText.replace(" ", "T")
            )

            return Qt.formatDateTime(
                date,
                "MM.dd  HH:mm"
            )
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

        case "EDIT":
            return "상품 수정"

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
            return theme.surfaceSoft
        }
    }
}