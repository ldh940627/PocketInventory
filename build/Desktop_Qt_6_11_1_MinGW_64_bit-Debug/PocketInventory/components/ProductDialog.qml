import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    required property var inventoryViewModel

    modal: true
    width: 430

    anchors.centerIn: parent

    standardButtons: Dialog.NoButton

    AppTheme {
        id: theme
    }

    onOpened: {
        nameField.clear()
        quantityField.clear()
        minimumField.clear()
        unitPriceField.clear()
        categoryField.clear()
        nameField.forceActiveFocus()
    }

    ColumnLayout {
        width: parent.width
        spacing: 18

        Label {
            text: "새 상품 등록"

            font.pixelSize: 20
            font.bold: true

            color: theme.textPrimary
        }

        Label {
            text: "상품 기본 정보와 초기 재고를 입력하세요."

            font.pixelSize: 12
            color: theme.textSecondary
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "상품명"
                font.pixelSize: 13
                font.bold: true
                color: theme.textPrimary
            }

            TextField {
                id: nameField

                Layout.fillWidth: true
                Layout.preferredHeight: 42

                placeholderText: "예: 볼트 M10"

                background: Rectangle {
                    radius: 7
                    color: theme.surface

                    border.width: 1
                    border.color:
                        nameField.activeFocus
                        ? theme.primary
                        : theme.border
                }
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
                    font.pixelSize: 13
                    font.bold: true
                    color: theme.textPrimary
                }

                TextField {
                    id: quantityField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 42

                    placeholderText: "0"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator {
                        bottom: 0
                    }

                    background: Rectangle {
                        radius: 7
                        color: theme.surface

                        border.width: 1
                        border.color:
                            quantityField.activeFocus
                            ? theme.primary
                            : theme.border
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6

                Label {
                    text: "최소 재고"
                    font.pixelSize: 13
                    font.bold: true
                    color: theme.textPrimary
                }

                TextField {
                    id: minimumField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 42

                    placeholderText: "0"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator {
                        bottom: 0
                    }

                    background: Rectangle {
                        radius: 7
                        color: theme.surface

                        border.width: 1
                        border.color:
                            minimumField.activeFocus
                            ? theme.primary
                            : theme.border
                    }
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "단가"
                font.pixelSize: 13
                font.bold: true
                color: theme.textPrimary
            }

            TextField {
                id: unitPriceField

                Layout.fillWidth: true
                Layout.preferredHeight: 42

                placeholderText: "예: 1500"

                inputMethodHints: Qt.ImhDigitsOnly

                validator: IntValidator {
                    bottom: 0
                }

                background: Rectangle {
                    radius: 7
                    color: theme.surface

                    border.width: 1
                    border.color:
                        unitPriceField.activeFocus
                        ? theme.primary
                        : theme.border
                }
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            spacing: 6

            Label{
                text: "카테고리"
                font.pixelSize: 13
                font.bold: true
                color: theme.textPrimary
            }

            TextField{
                id:categoryField

                Layout.fillWidth: true
                Layout.preferredHeight: 42
                placeholderText: "예 : 부품"

                background: Rectangle{
                    radius: 7
                    color: theme.surface
                    border.width: 1
                    border.color: categoryField.activeFocus ? theme.primary : theme.border
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "취소"

                implicitWidth: 80
                implicitHeight: 38

                onClicked: {
                    root.close()
                }
            }

            Button {
                id: addButton

                text: "상품 등록"

                implicitWidth: 96
                implicitHeight: 38

                onClicked: {
                    const succeeded =
                        root.inventoryViewModel.addProduct(
                            nameField.text, quantityField.text, minimumField.text,
                            unitPriceField.text, categoryField.text
                        )

                    if(succeeded) {
                        root.close()
                    }
                }

                contentItem: Text {
                    text: addButton.text

                    color: "white"

                    font.pixelSize: 12
                    font.bold: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        addButton.hovered
                        ? theme.primaryHover
                        : theme.primary
                }
            }
        }
    }
}