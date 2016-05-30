/*
 * Copyright 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
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
            title: "Select Calendars";
            delegate: Item {
                CheckBox {
                    id: checkbox
                    visible: styleData.value["enabled"]
                    checked: styleData.value["checked"]
                    onCheckedChanged: {
                        if (checked == styleData.value["checked"]) {
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
            height: Math.min(checkboxSize.implicitHeight, Math.max(16, TextSingleton.implicitHeight * 1.2)) + 4
            border {
                left: 4
                right: 4
            }
        }
    }
}
