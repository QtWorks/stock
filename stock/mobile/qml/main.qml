
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2018 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick 2.7

ApplicationWindow {
    id: appWindow
    visible: true
    width: 400
    height: 600

    Menu {
        id: menu
        x: menuButton.x
        y: menuButton.y

        MenuItem {
            text: qsTr( "Change Password" )
            onTriggered: {
                while( stackView.depth > 1 )
                    stackView.pop();

                appWindow.loggedIn = false
                menuButton.enabled = false
            }
        }
    }

    header: ToolBar {
        id: toolBar

        RowLayout {
            anchors.fill: parent

            Label {
                text: qsTr( "Stock" )
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                id: menuButton
                text: qsTr( "⋮" )
                onClicked: menu.open()
                enabled: false
            }
        }
    }

    footer: Label {
        id: connectionState
        text: qsTr( "Disconnected" )
    }

    Component {
        id: connectComponent

        Connect {
            pwd: password

            Component.onCompleted: {
                qmlCppSignals.connectRequest.connect( connectRequested )
            }
        }
    }

    Component {
        id: actionsComponent

        Actions {
        }
    }

    Component {
        id: busyComponent

        Busy {
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        property bool keyBackEnabled: true
        focus: true

        Keys.onReleased: {
            if( event.key === Qt.Key_Back && stackView.depth > 2 &&
                 keyBackEnabled ) {
                     stackView.pop();
                     event.accepted = true;
             }
        }

        initialItem: connectComponent
    }

    Component.onCompleted: {
        if( passwordSet ) {
            stackView.keyBackEnabled = false
            stackView.push( busyComponent )
        }
    }

    function connectRequested( pwd ) {
        password = pwd
        stackView.keyBackEnabled = false
        stackView.push( busyComponent )
        connectionState.text = qsTr( "Disconnected" )
    }

    Connections {
        target: qmlCppSignals

        onConnectionEstablished: {
            stackView.pop()
            stackView.push( actionsComponent )
            stackView.keyBackEnabled = true
            connectionState.text = qsTr( "Connected" )
            menuButton.enabled = true
        }
    }
}
