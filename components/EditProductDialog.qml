import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Dialog {
    id: root

    required property var inventoryViewModel

    property int proxyIndex : -1
    property string productName: ""
    property int currentQuantity: 0
    property int minimumQuantity: 0
    property int unitPrice: 0

    modal: true

    width : 440

    anchors.centerIn: parent

    standardButtons: Dialog.NoButton

    AppTheme{
        id: theme
    }

    function openEdit(index, name, quantity, minimum, price){
        root.proxyIndex = index
        root.productName = name
        root.currentQuantity = quantity
        root.minimumQuantity = minimum
        root.unitPrice = price

        root.open()
    }

    onOpened: {
        nameField.text = root.productName
        minimumField.text = String(root.minimumQuantity)
        unitPriceField.text = String(root.unitPrice)

        nameField.forceActiveFocus()
        nameField.selectAll()
    }

    // ============================================================
    // Header
    // ============================================================

    ColumnLayout{
        width: parent.width

        spacing: 18

        ColumnLayout{
            Layout.fillWidth: true

            spacing: 4

            Label{
                text: "상품 정보 수정"

                font.pixelSize: 21
                font.bold: true

                color: theme.textPrimary
            }

            Label{
                text: "상품명, 최소 재고, 단가를 수정할 수 있습니다."

                font.pixelSize: 12

                color: theme.textSecondary
            }
        }

        // ============================================================
        // Current Stock
        // 현재 수량은 수정 불가
        // ============================================================

        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: 60

            radius: 8

            color: theme.surfaceSoft

            RowLayout{
                anchors.fill: parent
                anchors.margins: 14

                Label{
                    text: "현재 재고"

                    color: theme.textSecondary
                    font.pixelSize: 13
                }

                Item{
                    Layout.fillWidth: true
                }

                Label{
                    text: root.currentQuantity + "개"

                    color: theme.textPrimary

                    font.pixelSize: 17
                    font.bold: true
                }
            }
        }

        // ============================================================
        // Product Name
        // ============================================================

        ColumnLayout{
            Layout.fillWidth: true

            spacing: 6

            Label{
                text: "상품명"

                font.pixelSize: 13
                font.bold: true

                color: theme.textPrimary
            }

            TextField{
                id: nameField

                Layout.fillWidth: true
                Layout.preferredHeight: 42

                placeholderText: "상품명을 입력하세요"

                leftPadding: 12
                rightPadding: 12

                background: Rectangle{
                    radius: 7

                    color: theme.surface

                    border.width: 1

                    border.color: nameField.activeFocus ? theme.primary : theme.border
                }
            }
        }

        // ============================================================
        // Minimum / Unit Price
        // ============================================================

        RowLayout{
            Layout.fillWidth: true

            spacing: 12

            ColumnLayout{
                Layout.fillWidth: true

                spacing: 6

                Label{
                    text: "최소 재고"

                    font.pixelSize: 13
                    font.bold: true

                    color: theme.textPrimary
                }

                TextField{
                    id: minimumField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 42

                    placeholderText: "0"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator{
                        bottom: 0
                    }

                    leftPadding: 12
                    rightPadding: 12

                    background: Rectangle{
                        radius: 7

                        color: theme.surface

                        border.width: 1

                        border.color: minimumField.activeFocus ? theme.primary : theme.border
                    }
                }
            }

            // --------------------------------------------------------
            // Unit Price
            // --------------------------------------------------------

            ColumnLayout{
                Layout.fillWidth: true

                spacing: 6

                Label{
                    text: "단가"

                    font.pixelSize: 13
                    font.bold: true

                    color: theme.textPrimary
                }

                TextField{
                    id: unitPriceField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 42

                    placeholderText: "0"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator{
                        bottom: 0
                    }

                    leftPadding: 12
                    rightPadding: 12

                    background:Rectangle{
                        radius: 7

                        color: theme.surface

                        border.width: 1

                        border.color: unitPriceField.activeFocus ? theme.primary : theme.border
                    }
                }
            }
        }

        // ============================================================
        // Preview
        // ============================================================

        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: 68

            radius: 8

            color: theme.surfaceSoft

            RowLayout {
                anchors.fill: parent
                anchors.margins: 14

                ColumnLayout {
                    spacing: 2

                    Label{
                        text: "현재 재고 금액"

                        color: theme.textSecondary
                        font.pixelSize: 12
                    }

                    Label{
                        text: Number(root.currentQuantity *(parseInt(unitPriceField.text) || 0)).toLocaleString(Qt.locale("ko_KR"), "f", 0) + "원"

                        color: theme.textPrimary

                        font.pixelSize: 17
                        font.bold: true
                    }
                }

                Item{
                    Layout.fillWidth: true
                }
            }
        }

        // ============================================================
        // Buttons
        // ============================================================

        RowLayout{
            Layout.fillWidth: true

            spacing: 8

            Item{
                Layout.fillWidth: true
            }

            Button{
                text: "취소"

                implicitWidth: 80
                implicitHeight: 38

                onClicked:{
                    root.close()
                }
            }

            Button{
                id: saveButton

                text: "저장"

                implicitWidth: 84
                implicitHeight: 38

                enabled: nameField.text.trim().length > 0
                && minimumField.text.length > 0
                && unitPriceField.text.length > 0

                onClicked:{
                    const succeeded = root.inventoryViewModel.updateProduct(
                                        root.proxyIndex,
                                        nameField.text,
                                        minimumField.text,
                                        unitPriceField.text)

                    if(succeeded){
                        root.close()
                    }
                }

                contentItem: Text{
                    text: saveButton.text

                    color: saveButton.enabled ? "White" : theme.textMuted

                    font.pixelSize: 13
                    font.bold: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle{
                    radius: 7

                    color: !saveButton.enabled ? "#E5E7EB" : saveButton.hovered ? theme.primaryHover : theme.primary
                }
            }
        }
    }
}
