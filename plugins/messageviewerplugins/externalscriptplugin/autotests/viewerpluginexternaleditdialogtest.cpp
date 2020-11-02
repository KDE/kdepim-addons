/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditdialogtest.h"

#include "../configuredialog/viewerpluginexternaleditdialog.h"
#include "../configuredialog/viewerpluginexternaleditwidget.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QTest>

ViewerPluginExternalEditDialogTest::ViewerPluginExternalEditDialogTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalEditDialogTest::~ViewerPluginExternalEditDialogTest()
{
}

void ViewerPluginExternalEditDialogTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditDialog dlg;

    auto *mEditWidget = dlg.findChild<ViewerPluginExternalEditWidget *>(QStringLiteral("editwidget"));
    QVERIFY(mEditWidget);

    auto *buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
}

QTEST_MAIN(ViewerPluginExternalEditDialogTest)
