import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: root

    required property int index
    required property string productName
    required property int productQuantity
    required property int minimumQuantity

    property bool filterMatched: true

    signal decreaseRequested(int productIndex)
    signal increaseRequested(int productIndex)
    signal deleteRequested(int productIndex)

    signal receiveRequested(int productIndex, string quantityText)
    signal releaseRequested(int productIndex, string quantityText)

    height: 90
    visible: true

    color: productQuantity <= minimumQuantity ? "#ffe5e5" : "#f2f2f2"

    radius: 8

    RowLayout{
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        Label{
            text: productName
            font.pixelSize: 18
            Layout.fillWidth: true
        }

        TextField {
            id: amountField

            Layout.preferredWidth: 80

            placeholderText: "수량"

            inputMethodHints:
                Qt.ImhDigitsOnly

            validator: IntValidator {
                bottom: 1
            }
        }

        Button {
            text: "입고"

            onClicked: {
                root.receiveRequested(
                    root.index,
                    amountField.text
                )
            }
        }

        Button {
            text: "출고"

            onClicked: {
                root.releaseRequested(
                    root.index,
                    amountField.text
                )
            }
        }

        Label{
            text: "최소 재고: " + minimumQuantity + "개"
            font.pixelSize: 13
            color: "gray"
        }

        Label{
            visible: productQuantity <= minimumQuantity
            text: "재고 부족"
            color: "red"
            font.bold: true
        }

        Button{
            text: "-"

            onClicked: {
                root.decreaseRequested(root.index)
            }
        }

        Label{
            text:productQuantity + "개"
            font.pixelSize: 18
            font.bold: true

            Layout.preferredWidth: 70
            horizontalAlignment: Text.AlignHCenter
        }

        Button{
            text: "+"
            onClicked:{
                root.increaseRequested(root.index)
            }
        }

        Button{
            text: "삭제"

            onClicked: {
                root.deleteRequested(root.index)
            }
        }
    }
}
