import QtQuick

QtObject {
    // =========================
    // Base
    // =========================

    readonly property color background: "#F7F8FA"

    readonly property color surface: "#FFFFFF"
    readonly property color surfaceSoft: "#FAFBFC"
    readonly property color surfaceHover: "#F5F6F8"

    // =========================
    // Sidebar
    // =========================

    readonly property color sidebar: "#111827"
    readonly property color sidebarHover: "#182131"
    readonly property color sidebarSelected: "#202C40"

    // =========================
    // Primary
    // =========================

    readonly property color primary: "#4F6EF7"
    readonly property color primaryHover: "#405BD8"
    readonly property color primarySoft: "#EEF2FF"

    // =========================
    // Text
    // =========================

    readonly property color textPrimary: "#111827"
    readonly property color textSecondary: "#667085"
    readonly property color textMuted: "#98A2B3"

    // =========================
    // Border
    // =========================

    readonly property color border: "#E7E9EE"
    readonly property color borderStrong: "#D9DDE5"

    // =========================
    // Status
    // =========================

    readonly property color success: "#16A66A"
    readonly property color successSoft: "#ECFDF3"

    readonly property color warning: "#E79A24"
    readonly property color warningSoft: "#FFF7E8"

    readonly property color danger: "#E5484D"
    readonly property color dangerSoft: "#FFF1F2"

    // =========================
    // Layout
    // =========================

    readonly property int sidebarWidth: 208

    readonly property int pageMaxWidth: 1180
    readonly property int pageMargin: 28

    readonly property int sectionSpacing: 18

    // =========================
    // Radius
    // =========================

    readonly property int radiusSmall: 6
    readonly property int radiusMedium: 8
    readonly property int radiusLarge: 12
}