import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 500
    height: 650
    visible: true
    title: qsTr("내 손안의 재고")

    ListModel{
        id: productModel
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 30
        spacing: 15

        Label{
            text: "상품 등록"
            font.pixelSize: 26
            font.bold: true
        }

        Label{
            id: messageLabel

            text:""
            visible: text !== ""

            Layout.fillWidth: true

            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap

            color: "green"
            font.pixelSize: 15
        }

        Label{
            text: "상품명"
        }

        TextField{
            id: nameField

            Layout.fillWidth: true
            placeholderText: "상품명을 입력하세요"
        }

        Label{
            text: "현재 수량"
        }

        TextField{
            id: quantityField

            Layout.fillWidth: true
            placeholderText: "수량을 입력하세요"

            inputMethodHints: Qt.ImhDigitsOnly

            validator: IntValidator{
                bottom: 0
            }
        }


        Button{
            text: "상품등록"

            Layout.fillWidth: true

            onClicked:{
               if(nameField.text === ""){
                   messageLabel.text = "상품명을 입력하세요."
                   messageLabel.color = "red"
                   return
               }

               if(quantityField.text === "")
               {
                   messageLabel.text = "수량을 입력하세요."
                   messageLabel.color = "red"
                   return
               }

               productModel.append({
                    productName:nameField.text,
                    productQuantity:Number(quantityField.text)
                })

               messageLabel.text = nameField.text.trim() + "상품이 등록되었습니다."
               messageLabel.color = "green"

               nameField.text = ""
               quantityField.text = ""
               nameField.forceActiveFocus()
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "lightgray"
        }

        Label {
            text: "상품 목록"
            font.pixelSize: 22
            font.bold: true
        }

        ListView {
            id: productListView

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: productModel

            spacing: 8

            delegate: Rectangle {

                required property int index
                required property string productName
                required property int productQuantity

                width: productListView.width
                height: 70

                color: "#f2f2f2"
                radius: 8

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 8

                    Label {
                        text: productName
                        font.pixelSize: 18

                        Layout.fillWidth: true
                    }

                    Button{
                        text: "-"

                        onClicked: {
                            if(productQuantity > 0){
                                const newQuantity = productQuantity - 1
                                productModel.setProperty(
                                    index,
                                    "productQuantity",
                                    newQuantity
                                )

                                messageLabel.text = productName
                                + "수량을" + newQuantity + "개로 변경했습니다."
                                messageLabel.color = "green"
                            } else {
                                messageLabel.text = "재고는 0개보다 작을 수 없습니다."
                                messageLabel.color = "red"
                            }
                        }
                    }

                    Label {
                        text: productQuantity + "개"
                        font.pixelSize: 18
                        font.bold: true

                        Layout.preferredWidth: 70
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Button{
                        text: "+"

                        onClicked: {
                            const newQuantity = productQuantity + 1
                            productModel.setProperty(
                                        index,
                                        "productQuantity",
                                        newQuantity)
                            messageLabel.text = productName + "수량을"
                            + newQuantity + "개로 변경했습니다."
                            messageLabel.color = "green"
                        }
                    }

                    Button {
                        text: "삭제"

                        onClicked: {
                            const deletedName = productName

                            productModel.remove(index)

                            messageLabel.text = deletedName + "상품을 삭제했습니다."
                            messageLabe.color = "darkorange"
                        }
                    }
                }
            }
        }

    }
}
