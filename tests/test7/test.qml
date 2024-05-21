ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Nested QML Example"

    Rectangle {
        id: rect1
        visible: true
        width: 800
        height: 600
        title: "Advanced QML with JavaScript Example"

        Rectangle {
            id: mainRect
            width: parent.width
            height: parent.height
            color: "#f0f0f0"

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 20

                Text {
                    text: "Advanced QML with JavaScript"
                    font.pixelSize: 24
                    Layout.alignment: Qt.AlignCenter
                }

                RowLayout {
                    spacing: 10
                    Layout.alignment: Qt.AlignCenter

                    Button {
                        id: button1
                        text: "Button 1"
                    }

                    Button {
                        id: button2
                        text: "Button 2"
                    }

                    Button {
                        id: button3
                        text: "Button 3"
                    }
                }

                Rectangle {
                    width: 200
                    height: 100
                    color: "#ffcc00"
                    radius: 10

                    Text {
                        id: messageLabel
                        text: "Press a button"
                        anchors.centerIn: parent
                        font.pixelSize: 18
                    }
                }

                Slider {
                    id: slider
                    width: 300
                    from: 0
                    to: 100
                    value: 50
                }

                ProgressBar {
                    id: progressBar
                    width: 300
                    value: slider.value
                }
            }
        }
    }
}

