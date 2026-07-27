import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    id: root

    property alias searchText: searchField.text

    signal searchRequested(string searchText)
    signal clearRequested()

    implicitHeight: 56
    radius: 8
    color: "#f2f2f2"

    RowLayout{
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        TextField{
            id: searchField
            Layout.fillWidth: true
            placeholderText: "상품명을 검색하세요"

            onTextChanged: {
                root.searchRequested(text)
            }

            Keys.onReturnPressed: {
                root.searchRequested(text)
            }
        }

        Button{
            text: "초기화"
            enabled: searchField.text.length > 0

            onClicked: {
                searchField.clear()
                searchField.forceActiveFocus()
                root.clearRequested()
                root.searchRequested("")
            }
        }

        function focusSearchField(){
            searchField.forceActiveFocus()
        }
    }
}
