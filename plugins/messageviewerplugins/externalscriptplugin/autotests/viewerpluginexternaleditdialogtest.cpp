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
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalEditDialogTest::ViewerPluginExternalEditDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ViewerPluginExternalEditDialogTest::~ViewerPluginExternalEditDialogTest() = default;

void ViewerPluginExternalEditDialogTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditDialog dlg;

    const auto mEditWidget = dlg.findChild<ViewerPluginExternalEditWidget *>(u"editwidget"_s);
    QVERIFY(mEditWidget);

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);
}

QTEST_MAIN(ViewerPluginExternalEditDialogTest)

#include "moc_viewerpluginexternaleditdialogtest.cpp"
