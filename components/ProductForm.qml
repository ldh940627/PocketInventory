import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    signal submitRequested(
        string productName,
        string productQuantity,
        string minimumQuantity)

    implicitHeight: formLayout.implicitHeight + 24

    radius: 8
    color: "#f2f2f2"

    ColumnLayout{
        id: formLayout

        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        Label{
            text: "상품 등록"
            font.pixelSize: 18
            font.bold: true
        }

        RowLayout{
            Layout.fillWidth: true
            spacing: 8

            TextField{
                id: nameField
                Layout.fillWidth: true
                placeholderText: "상품명"
                Keys.onReturnPressed:{
                    quantityField.forceActiveFocus()
                }
            }
        }

        TextField{
            id: quantityField

            Layout.preferredWidth: 130
            placeholderText: "현재 수량"
            inputMethodHints: Qt.ImhDigitsOnly
            validator: IntValidator{
                bottom: 0
            }
        }

        TextField{
            id:minimumQuantityField
            Layout.preferredWidth: 130
            placeholderText: "최소 수량"
            inputMethodHints: Qt.ImhDigitsOnly

            validator: IntValidator{
                bottom: 0
            }

            Keys.onReturnPressed:{
                root.requestSubmit()
            }

        }
        Button{
            text:"상품 등록"

            onClicked: {
                root.requestSubmit()
            }
        }

    }

    function requestSubmit(){
        root.submitRequested(
                    nameField.text,
                    quantityField.text,
                    minimumQuantityField.text)
    }

    function clearFields(){
        nameField.clear()
        quantityField.clear()
        minimumQuantityField.clear()
    }

    function focusNameField(){
        nameField.forceActiveFocus()
    }

    function resetForm(){
        clearFields()
        focusNameField()
    }

}
