import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    required property var inventoryViewModel

    property int proxyIndex: -1
    property string productName: ""

    modal: true

    width: 400

    anchors.centerIn: parent

    standardButtons:
        Dialog.NoButton

    AppTheme {
        id: theme
    }

    ColumnLayout {
        width: parent.width

        spacing: 18

        Label {
            text: "상품 삭제"

            font.pixelSize: 20
            font.bold: true

            color: theme.textPrimary
        }

        Label {
            Layout.fillWidth: true

            text:
                root.productName
                + " 상품을 삭제하시겠습니까?"

            wrapMode: Text.WordWrap

            color: theme.textSecondary
        }

        Label {
            Layout.fillWidth: true

            text:
                "상품은 재고 목록에서 제거되지만 "
                + "기존 변경 이력은 유지됩니다."

            wrapMode: Text.WordWrap

            color: theme.textMuted

            font.pixelSize: 12
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
                id: deleteButton

                text: "삭제"

                implicitWidth: 80
                implicitHeight: 38

                onClicked: {
                    root.inventoryViewModel.removeProduct(
                        root.proxyIndex
                    )

                    root.close()
                }

                contentItem: Text {
                    text: deleteButton.text

                    color: "white"

                    font.pixelSize: 12
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        deleteButton.hovered
                        ? "#C93C41"
                        : theme.danger
                }
            }
        }
    }

    function openDelete(
        proxyIndex,
        productName
    ) {
        root.proxyIndex = proxyIndex
        root.productName = productName

        root.open()
    }
}