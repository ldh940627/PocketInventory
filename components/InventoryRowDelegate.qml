import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property int index
    required property string productName
    required property int productQuantity
    required property int minimumQuantity
    required property int unitPrice

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

    signal editRequested(
        int proxyIndex,
        string productname,
        int currentQuantity,
        int minimumQuantity,
        int unitPrice
    )

    signal deleteRequested(
        int proxyIndex,
        string productName
    )

    AppTheme {
        id: theme
    }

    implicitHeight: 58

    color:
        hoverArea.containsMouse
        ? theme.surfaceHover
        : theme.surface

    // ============================================================
    // Row
    // ============================================================

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 18
        anchors.rightMargin: 12

        spacing: 12

        // =========================
        // Product
        // =========================

        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: 4

            spacing: 1

            Label {
                Layout.fillWidth: true

                text: root.productName

                color: theme.textPrimary

                font.pixelSize: 13
                font.bold: true

                elide: Text.ElideRight
            }
        }

        // =========================
        // Quantity
        // =========================

        Label {
            Layout.preferredWidth: 90

            text:
                root.productQuantity + "개"

            color: theme.textPrimary

            font.pixelSize: 13
            font.bold: true

            horizontalAlignment:
                Text.AlignHCenter
        }

        // =========================
        // Minimum
        // =========================

        Label {
            Layout.preferredWidth: 90

            text:
                root.minimumQuantity + "개"

            color: theme.textSecondary

            font.pixelSize: 12

            horizontalAlignment:
                Text.AlignHCenter
        }

        // =========================
        // Price
        // =========================

        Label {
            Layout.preferredWidth: 110

            text: Number(root.unitPrice).toLocaleString(Qt.locale("ko_KR"), "f", 0) + "원"

            color: theme.textPrimary

            font.pixelSize: 12

            horizontalAlignment: Text.AlignHCenter
        }

        // =========================
        // TotalPrice
        // =========================

        Label {
            Layout.preferredWidth: 120

            text : Number(root.productQuantity * root.unitPrice).toLocaleString(Qt.locale("ko_KR"), "f", 0) + "원"

            color: theme.textPrimary

            font.pixelSize: 12
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
        }

        // =========================
        // Status
        // =========================

        Item {
            Layout.preferredWidth: 90
            Layout.preferredHeight: 28

            Rectangle {
                anchors.centerIn: parent

                implicitWidth: statusLabel.implicitWidth + 20
                height: 24

                radius: 6

                color:
                    root.productQuantity <= root.minimumQuantity
                    ? theme.dangerSoft
                    : theme.successSoft

                Label {
                    id: statusLabel

                    anchors.centerIn: parent

                    text:
                        root.productQuantity <= root.minimumQuantity
                        ? "부족"
                        : "정상"

                    color:
                        root.productQuantity <= root.minimumQuantity
                        ? theme.danger
                        : theme.success

                    font.pixelSize: 11
                    font.bold: true
                }
            }
        }

        // =========================
        // Actions
        // =========================

        Item {
            Layout.preferredWidth: 36
            Layout.preferredHeight: 36

            Button {
                id: actionButton

                anchors.fill: parent

                text: "···"

                hoverEnabled: true

                onClicked: {
                    actionMenu.open()
                }

                contentItem: Text {
                    text: actionButton.text

                    color: theme.textSecondary

                    font.pixelSize: 16
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 6

                    color:
                        actionButton.hovered
                        ? theme.surfaceHover
                        : "transparent"
                }

                Menu {
                    id: actionMenu

                    y: actionButton.height + 4

                    MenuItem {
                        text: "재고 입고"

                        onTriggered: {
                            root.receiveRequested(
                                root.index,
                                root.productName,
                                root.productQuantity
                            )
                        }
                    }

                    MenuItem {
                        text: "재고 출고"

                        onTriggered: {
                            root.releaseRequested(
                                root.index,
                                root.productName,
                                root.productQuantity
                            )
                        }
                    }

                    MenuSeparator {
                    }

                    MenuItem{
                        text: "상품 수정"

                        onTriggered:{
                            root.editRequested(
                                root.index,
                                root.productName,
                                root.productQuantity,
                                root.minimumQuantity,
                                root.unitPrice
                            )
                        }
                    }

                    MenuItem {
                        text: "상품 삭제"

                        onTriggered: {
                            root.deleteRequested(
                                root.index,
                                root.productName
                            )
                        }
                    }
                }
            }
        }
    }

    // ============================================================
    // Hover
    // ============================================================

    MouseArea {
        id: hoverArea

        anchors.fill: parent

        hoverEnabled: true
        acceptedButtons: Qt.NoButton
    }

    // ============================================================
    // Separator
    // ============================================================

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 1

        color: theme.border
    }
}