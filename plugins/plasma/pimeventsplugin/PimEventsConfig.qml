/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

import QtQuick 2.0
import QtQuick.Controls 1.4
// gives us TextSingleton
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import org.kde.plasma.core 2.0
import org.kde.plasma.PimCalendars 1.0

Item {
    id: pimEventsConfig
    width: parent.width
    height: parent.height

    signal configurationChanged

    function saveConfig()
    {
        calendarModel.saveConfig();
    }

    PimCalendarsModel {
            id: calendarModel
    }

    // Invisible, used to measure implicitHeight of checkboxes so we can
    // adjust row height in rowDelegate
    CheckBox {
        id: checkboxSize
        visible: false
    }

    TreeView {
        id: calendarTreeView;

        anchors.fill: parent

        model: calendarModel

        TableViewColumn {
            role: "data"
            title: i18n("Select Calendars");
            delegate: Item {
                CheckBox {
                    id: checkbox
                    visible: styleData.value["enabled"]
                    checked: styleData.value["checked"]
                    onCheckedChanged: {
                        if (checked === styleData.value["checked"]) {
                            return;
                        }
                        calendarModel.setChecked(styleData.value["id"], checked);
                        pimEventsConfig.configurationChanged();
                    }
                    width: 24
                    height: 24
                }
                IconItem {
                    id: icon
                    anchors.left: checkbox.visible ? checkbox.right : parent.left
                    visible: valid
                    source: styleData.value["iconName"]
                    height: 20
                    width: 20
                }
                Text {
                    anchors.left: icon.visible ? icon.right : checkbox.visible ? checkbox.right : parent.left
                    renderType: Text.NativeRendering

                    text: styleData.value["name"]
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    color: styleData.textColor
                    height: 24
                }
            }
        }

        // Based on Desktop.TableViewStyle
        rowDelegate: BorderImage {
            visible: styleData.selected || styleData.alternate
            source: "image://__tablerow/" + (styleData.alternate ? "alternate_" : "")
                        + (styleData.selected ? "selected_" : "")
                        + (calendarTreeView.activeFocus ? "active" : "")
            // Make sure the checkbox always fits, add 4 for some small margin
            height: Math.ceil( Math.min(checkboxSize.implicitHeight, Math.max(16, TextSingleton.implicitHeight * 1.2)) + 4 )
            border {
                left: 4
                right: 4
            }
        }
    }
}
