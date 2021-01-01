/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSWIDGETTEST_H
#define FOLDERCONFIGURESETTINGSWIDGETTEST_H

#include <QObject>

class FolderConfigureSettingsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsWidgetTest(QObject *parent = nullptr);
    ~FolderConfigureSettingsWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // FOLDERCONFIGURESETTINGSWIDGETTEST_H
