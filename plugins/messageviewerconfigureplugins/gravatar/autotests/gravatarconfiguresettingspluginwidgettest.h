/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARCONFIGURESETTINGSPLUGINWIDGETTEST_H
#define GRAVATARCONFIGURESETTINGSPLUGINWIDGETTEST_H

#include <QObject>

class GravatarConfigureSettingsPluginWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginWidgetTest(QObject *parent = nullptr);
    ~GravatarConfigureSettingsPluginWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAVATARCONFIGURESETTINGSPLUGINWIDGETTEST_H
