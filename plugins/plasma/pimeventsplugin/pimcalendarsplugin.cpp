/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "pimcalendarsmodel.h"

class PimCalendarsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri) override
    {
        qmlRegisterType<PimCalendarsModel>(uri, 1, 0, "PimCalendarsModel");
    }
};

#include "pimcalendarsplugin.moc"
