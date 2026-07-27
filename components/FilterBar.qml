import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{

    id:root

    property string selectedFilter: "all"

    signal filterChanged(string filter)

    implicitHeight: 56
    radius: 8
    color: "#f2f2f2"

    RowLayout{
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        Label{
            text: "재고 상태"
            font.bold: true
        }

        Item{
            Layout.fillWidth: true
        }

        Button{
            text: "전체"
            checkable: true
            checked: root.selectedFilter === "all"

            onClicked:{
                root.selectFilter("all")
            }
        }

        Button{
            text: "정상"
            checkable: true
            checked: root.selectedFilter === "normal"

            onClicked:{
                root.selectFilter("normal")
            }
        }

        Button{
            text: "부족"
            checkable: true
            checked: root.selectedFilter === "low"

            onClicked:{
                root.selectFilter("low")
            }
        }

    }

    function selectFilter(filter){
        if(root.selectedFilter === filter)
            return

        root.selectedFilter = filter
        root.filterChanged(filter)

    }

    function resetFilter(){
        root.selectFilter("all")
    }

}
