import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property var inventoryViewModel

    signal receiveRequested(
        int proxyIndex,
        string productName,
        int currentQuantity
    )

    signal releaseRequested(
        int proxyIndex,
        string productName,
        int currentQuantity
    )

    signal deleteRequested(
        int proxyIndex,
        string productName
    )

    AppTheme {
        id: theme
    }

    radius: theme.radiusLarge

    color: theme.surface

    border.width: 1
    border.color: theme.border

    clip: true

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        // ========================================================
        // Header
        // ========================================================

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 44

            color: theme.surfaceSoft

            RowLayout {
                anchors.fill: parent

                anchors.leftMargin: 18
                anchors.rightMargin: 12

                spacing: 12

                Label {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 4

                    text: "상품"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true
                }

                Label {
                    Layout.preferredWidth: 90

                    text: "현재 재고"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter
                }

                Label {
                    Layout.preferredWidth: 90

                    text: "최소 재고"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter
                }

                Label {
                    Layout.preferredWidth: 110
                    text: "단가"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true

                    horizontalAlignment: Text.AlignHCenter
                }

                Label {
                    Layout.preferredWidth: 120

                    text: "재고 금액"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true

                    horizontalAlignment: Text.AlignHCenter
                }

                Label {
                    Layout.preferredWidth: 90

                    text: "상태"

                    color: theme.textSecondary

                    font.pixelSize: 11
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter
                }

                Item {
                    Layout.preferredWidth: 36
                }
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                height: 1

                color: theme.border
            }
        }

        // ========================================================
        // List
        // ========================================================

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: productList

                anchors.fill: parent

                clip: true

                model:
                    root.inventoryViewModel.products

                spacing: 0

                delegate: InventoryRowDelegate {
                    width: productList.width

                    onReceiveRequested:
                        function(
                            proxyIndex,
                            productName,
                            currentQuantity
                        ) {
                            root.receiveRequested(
                                proxyIndex,
                                productName,
                                currentQuantity
                            )
                        }

                    onReleaseRequested:
                        function(
                            proxyIndex,
                            productName,
                            currentQuantity
                        ) {
                            root.releaseRequested(
                                proxyIndex,
                                productName,
                                currentQuantity
                            )
                        }

                    onDeleteRequested:
                        function(
                            proxyIndex,
                            productName
                        ) {
                            root.deleteRequested(
                                proxyIndex,
                                productName
                            )
                        }
                }
            }

            // ====================================================
            // Empty State
            // ====================================================

            ColumnLayout {
                anchors.centerIn: parent

                visible:
                    root.inventoryViewModel.filteredCount === 0

                spacing: 4

                Label {
                    Layout.alignment: Qt.AlignHCenter

                    text:
                        root.inventoryViewModel.totalCount === 0
                        ? "등록된 상품이 없습니다."
                        : "조건에 맞는 상품이 없습니다."

                    color: theme.textSecondary

                    font.pixelSize: 13
                }

                Label {
                    Layout.alignment: Qt.AlignHCenter

                    visible:
                        root.inventoryViewModel.totalCount > 0

                    text:
                        "검색어나 필터 조건을 변경해보세요."

                    color: theme.textMuted

                    font.pixelSize: 11
                }
            }
        }
    }
}