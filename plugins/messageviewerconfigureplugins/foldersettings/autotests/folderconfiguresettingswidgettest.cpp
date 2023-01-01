/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingswidgettest.h"
#include "../folderconfiguresettingswidget.h"
#include <QTest>
QTEST_MAIN(FolderConfigureSettingsWidgetTest)
FolderConfigureSettingsWidgetTest::FolderConfigureSettingsWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void FolderConfigureSettingsWidgetTest::shouldHaveDefaultValues()
{
    FolderConfigureSettingsWidget w;
    // TODO
}
