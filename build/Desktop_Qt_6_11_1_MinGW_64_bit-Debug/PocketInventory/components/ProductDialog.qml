import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    required property var inventoryViewModel

    modal: true

    width: 430

    anchors.centerIn: parent

    title: "상품 등록"

    standardButtons: Dialog.NoButton

    onOpened: {
        nameField.forceActiveFocus()
    }

    ColumnLayout {
        width: parent.width

        spacing: 16

        Label {
            text: "새 상품 등록"

            font.pixelSize: 20
            font.bold: true
        }

        Label {
            text:
                "상품 정보와 초기 재고를 입력하세요."

            color: "#6B7280"
        }

        ColumnLayout {
            Layout.fillWidth: true

            spacing: 6

            Label {
                text: "상품명"

                font.bold: true
            }

            TextField {
                id: nameField

                Layout.fillWidth: true

                placeholderText:
                    "예: 볼트 M10"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            spacing: 12

            ColumnLayout {
                Layout.fillWidth: true

                spacing: 6

                Label {
                    text: "현재 수량"
                    font.bold: true
                }

                TextField {
                    id: quantityField

                    Layout.fillWidth: true

                    placeholderText: "0"

                    inputMethodHints:
                        Qt.ImhDigitsOnly

                    validator: IntValidator {
                        bottom: 0
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true

                spacing: 6

                Label {
                    text: "최소 재고"
                    font.bold: true
                }

                TextField {
                    id: minimumField

                    Layout.fillWidth: true

                    placeholderText: "0"

                    inputMethodHints:
                        Qt.ImhDigitsOnly

                    validator: IntValidator {
                        bottom: 0
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "취소"

                onClicked: {
                    root.close()
                }
            }

            Button {
                text: "상품 등록"

                onClicked: {
                    const succeeded =
                        root.inventoryViewModel.addProduct(
                            nameField.text,
                            quantityField.text,
                            minimumField.text
                        )

                    if (!succeeded)
                        return

                    nameField.clear()
                    quantityField.clear()
                    minimumField.clear()

                    root.close()
                }
            }
        }
    }
}