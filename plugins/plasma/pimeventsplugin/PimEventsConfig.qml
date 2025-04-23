/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigamiaddons.delegates as Delegates
import org.kde.kitemmodels
import org.kde.kirigami as Kirigami
import org.kde.kcmutils as KCMUtils
import org.kde.CalendarEventsPlugin

KCMUtils.ScrollViewKCM {
    id: pimEventsConfig

    signal configurationChanged

    function saveConfig() {
        calendarModel.saveConfig();
    }

    view: ListView {
        currentIndex: -1

        clip: true // Avoid visual glitches
        focus: true // keyboard navigation
        activeFocusOnTab: true // keyboard navigation

        model: KDescendantsProxyModel {
            model: PimCalendarsModel {
                id: calendarModel
            }
        }

        delegate: Delegates.RoundedTreeDelegate {
            id: collection

            required property int collectionId
            required property string name
            required property string iconName
            required property bool isChecked
            required property bool isEnabled

            icon.name: iconName
            text: name

            contentItem: RowLayout {
                QQC2.CheckBox {
                    id: checkbox
                    visible: collection.isEnabled
                    checked: collection.isChecked
                    onCheckedChanged: {
                        if (checked === collection.isChecked) {
                            return;
                        }
                        calendarModel.setChecked(collection.collectionId, checked);
                        pimEventsConfig.configurationChanged();
                    }
                }

                Delegates.DefaultContentItem {
                    itemDelegate: collection
                }
            }
        }
    }
}
