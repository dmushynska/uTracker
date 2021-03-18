pragma Singleton

import QtQuick 2.4


QtObject {
    id: __theme

    property bool isClassic: true
    property string back: !isClassic ? "#dab6c2" : "#80808F"
    property string font: !isClassic ? "#7a163c" : "grey"
    property string font_: !isClassic ? "#7a163c" : "white"
    property string primary: !isClassic ? "#fad2e0" : "#80808F"
    property string accent: !isClassic ? "#ffdad8" : "#7D7F8E"
    property string task: !isClassic ? "#fde8f5" : "#fbfaf6"
    property string gradienter: !isClassic ? "#dab6c2" : "#80808F"
    property string backBack: !isClassic ? "#dab6c2" : "#e4e1e0"
    property string headerBack: !isClassic ? "#80f6a2bf" : "#5a585c"
    property string addTask: !isClassic ? "#7a163c" : "#5a585c"
    property string addTaskFont: !isClassic ? "white" : "white"
    property string listBack: !isClassic ? "#fcd8e4" : "#8b8da0"
    property string overlay: !isClassic ? "#307a163c" : "#308b8da0"
    property string slider: !isClassic ? "#407a163c" : "#805a585c"
    property string sliderHover: !isClassic ? "#807a163c" : "#5a585c"
    property string sliderMain: !isClassic ? "#407a163c" : "#405a585c"
    property string sliderMainHover: !isClassic ? "#807a163c" : "#805a585c"
    property string desk: !isClassic ? "#ebc7d3" : "#f5f2f1"

    property string progress: !isClassic ? "#AEF100" : "#e0b864"

    property string infoHeader: !isClassic ? "#80f6a2bf" : "#f05a585c"
    property string infoHeaderFont: !isClassic ? "#7a163c" : "white"
    property string infoBack: !isClassic ? "#ebc7d3" : "#f08B8D96"
    property string infoUserBack: !isClassic ? "#fad2e0" : "#E7E6E2"
    property string infoUserFont: !isClassic ? "#7a163c" : "#5a585c"

    property string buttonBorder: !isClassic ? "#f6a2bf" : "#E7E6E2"
    property string buttonBack: !isClassic ? "#fad2e0" : "#5a585c"
    property string buttonBackHover: !isClassic ? "#ffdad8" : "#8b8da0"
    property string buttonFont: !isClassic ? "#7a163c" : "white"

    property string inputBorder: !isClassic ? "#f6a2bf" : "#5a585c"
    property string inputBack: !isClassic ? "#fad2e0" : "#5a585c"
    property string inputBackHover: !isClassic ? "#ffdad8" : "#8b8da0"
    property string inputFont: !isClassic ? "#7a163c" : "white"
    function changeTheme() {
        isClassic = !isClassic
    }
}


