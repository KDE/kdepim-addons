/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditdialogtest.h"

#include "../configuredialog/viewerpluginexternaleditdialog.h"
#include "../configuredialog/viewerpluginexternaleditwidget.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>

ViewerPluginExternalEditDialogTest::ViewerPluginExternalEditDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ViewerPluginExternalEditDialogTest::~ViewerPluginExternalEditDialogTest() = default;

void ViewerPluginExternalEditDialogTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditDialog dlg;

    auto mEditWidget = dlg.findChild<ViewerPluginExternalEditWidget *>(QStringLiteral("editwidget"));
    QVERIFY(mEditWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
}

QTEST_MAIN(ViewerPluginExternalEditDialogTest)

#include "moc_viewerpluginexternaleditdialogtest.cpp"
