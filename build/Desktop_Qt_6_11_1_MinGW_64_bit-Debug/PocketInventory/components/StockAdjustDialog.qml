import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    required property var inventoryViewModel

    property int proxyIndex: -1
    property string productName: ""
    property int currentQuantity: 0

    // receive / release
    property string mode: "receive"

    readonly property bool isReceive:
        root.mode === "receive"

    readonly property int inputQuantity: {
        const value = parseInt(quantityField.text)

        return isNaN(value)
            ? 0
            : value
    }

    readonly property int afterQuantity:
        root.isReceive
        ? root.currentQuantity + root.inputQuantity
        : root.currentQuantity - root.inputQuantity

    modal: true

    width: 420

    anchors.centerIn: parent

    standardButtons:
        Dialog.NoButton

    AppTheme {
        id: theme
    }

    onOpened: {
        quantityField.clear()
        quantityField.forceActiveFocus()
    }

    ColumnLayout {
        width: parent.width

        spacing: 20

        // ========================================================
        // Header
        // ========================================================

        ColumnLayout {
            Layout.fillWidth: true

            spacing: 4

            Label {
                text:
                    root.isReceive
                    ? "재고 입고"
                    : "재고 출고"

                font.pixelSize: 21
                font.bold: true

                color:
                    theme.textPrimary
            }

            Label {
                text:
                    root.productName

                font.pixelSize: 13

                color:
                    theme.textSecondary
            }
        }

        // ========================================================
        // Current Stock
        // ========================================================

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 64

            radius: 8

            color:
                theme.surfaceSoft

            RowLayout {
                anchors.fill: parent
                anchors.margins: 14

                Label {
                    text: "현재 재고"

                    color:
                        theme.textSecondary

                    font.pixelSize: 13
                }

                Item {
                    Layout.fillWidth: true
                }

                Label {
                    text:
                        root.currentQuantity
                        + "개"

                    color:
                        theme.textPrimary

                    font.pixelSize: 18
                    font.bold: true
                }
            }
        }

        // ========================================================
        // Quantity
        // ========================================================

        ColumnLayout {
            Layout.fillWidth: true

            spacing: 6

            Label {
                text:
                    root.isReceive
                    ? "입고 수량"
                    : "출고 수량"

                font.pixelSize: 13
                font.bold: true

                color:
                    theme.textPrimary
            }

            TextField {
                id: quantityField

                Layout.fillWidth: true
                Layout.preferredHeight: 42

                placeholderText:
                    "수량을 입력하세요"

                inputMethodHints:
                    Qt.ImhDigitsOnly

                validator: IntValidator {
                    bottom: 1
                }

                background: Rectangle {
                    radius: 7

                    color:
                        theme.surface

                    border.width: 1

                    border.color:
                        quantityField.activeFocus
                        ? theme.primary
                        : theme.border
                }
            }
        }

        // ========================================================
        // Preview
        // ========================================================

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 70

            radius: 8

            color:
                root.isReceive
                ? theme.successSoft
                : theme.warningSoft

            RowLayout {
                anchors.fill: parent
                anchors.margins: 14

                ColumnLayout {
                    spacing: 2

                    Label {
                        text:
                            "변경 후 재고"

                        color:
                            theme.textSecondary

                        font.pixelSize: 12
                    }

                    RowLayout {
                        spacing: 8

                        Label {
                            text:
                                root.currentQuantity
                                + "개"

                            color:
                                theme.textSecondary

                            font.pixelSize: 16
                        }

                        Label {
                            text: "→"

                            color:
                                theme.textMuted
                        }

                        Label {
                            text:
                                root.afterQuantity
                                + "개"

                            color:
                                root.afterQuantity < 0
                                ? theme.danger
                                : theme.textPrimary

                            font.pixelSize: 18
                            font.bold: true
                        }
                    }
                }

                Item {
                    Layout.fillWidth: true
                }
            }
        }

        // ========================================================
        // Warning
        // ========================================================

        Label {
            Layout.fillWidth: true

            visible:
                !root.isReceive
                && root.afterQuantity < 0

            text:
                "출고 수량이 현재 재고보다 많습니다."

            color:
                theme.danger

            font.pixelSize: 12
        }

        // ========================================================
        // Buttons
        // ========================================================

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
                id: confirmButton

                text:
                    root.isReceive
                    ? "입고하기"
                    : "출고하기"

                implicitWidth: 90
                implicitHeight: 38

                enabled:
                    root.inputQuantity > 0
                    && (
                        root.isReceive
                        || root.afterQuantity >= 0
                    )

                onClicked: {
                    let succeeded = false

                    if (root.isReceive) {
                        succeeded =
                            root.inventoryViewModel.receiveStock(
                                root.proxyIndex,
                                quantityField.text
                            )
                    } else {
                        succeeded =
                            root.inventoryViewModel.releaseStock(
                                root.proxyIndex,
                                quantityField.text
                            )
                    }

                    if (succeeded) {
                        root.close()
                    }
                }

                contentItem: Text {
                    text:
                        confirmButton.text

                    color:
                        confirmButton.enabled
                        ? "white"
                        : theme.textMuted

                    font.pixelSize: 13
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        !confirmButton.enabled
                        ? "#E5E7EB"
                        : confirmButton.hovered
                            ? theme.primaryHover
                            : theme.primary
                }
            }
        }
    }
    function openReceive(
        proxyIndex,
        productName,
        currentQuantity
    ) {
        root.proxyIndex = proxyIndex
        root.productName = productName
        root.currentQuantity = currentQuantity
        root.mode = "receive"

        root.open()
    }

    function openRelease(
        proxyIndex,
        productName,
        currentQuantity
    ) {
        root.proxyIndex = proxyIndex
        root.productName = productName
        root.currentQuantity = currentQuantity
        root.mode = "release"

        root.open()
    }
}