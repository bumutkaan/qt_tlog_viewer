import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15


Item {
    id: root

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    property var trackPoints: []

    Map {
        id: map

        anchors.fill: parent
        plugin: mapPlugin

        center: QtPositioning.coordinate(39.9334, 32.8597)
        zoomLevel: 14

        MapPolyline {
            id: trackLine

            line.width: 3
            path: root.trackPoints
        }

        MapQuickItem {
            id: vehicle

            coordinate: QtPositioning.coordinate(
                            39.9334,
                            32.8597)

            anchorPoint.x: vehicleIcon.width / 2
            anchorPoint.y: vehicleIcon.height / 2

            sourceItem: Rectangle {
                id: vehicleIcon

                width: 30
                height: 30

                radius: 15

                color: "red"

                Text {
                    anchors.centerIn: parent
                    text: "▲"
                    color: "white"
                    font.pixelSize: 20
                }
            }
        }
    }

    function updateTelemetry(lat, lon, heading)
    {
        var coordinate =
            QtPositioning.coordinate(lat, lon)

        vehicle.coordinate = coordinate

        // Rota ekle
        trackPoints.push(coordinate)

        // QML'e değişiklik olduğunu bildir
        trackLine.path = trackPoints

        // Haritayı takip et
        map.center = coordinate

    }

    function setIndex(lat, lon, heading)
    {
        var coordinate =
            QtPositioning.coordinate(lat, lon)

        vehicle.coordinate = coordinate

        // QML'e değişiklik olduğunu bildir
        trackLine.path = trackPoints

        // Haritayı takip et
        map.center = coordinate

    }

    function clearTrack()
    {
        trackPoints = []
        trackLine.path = []
    }

    function loggerFunction()
    {
        console.log("logger function")
    }

    function myQmlFunction(message) {
        console.log("QML received:", message)
        return "Success from QML!"
    }
}