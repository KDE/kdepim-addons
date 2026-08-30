/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfiguredialogtest.h"
#include "../configuredialog/viewerpluginexternalconfiguredialog.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalConfigureDialogTest::ViewerPluginExternalConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ViewerPluginExternalConfigureDialogTest::~ViewerPluginExternalConfigureDialogTest() = default;

void ViewerPluginExternalConfigureDialogTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QVERIFY(buttonBox->button(QDialogButtonBox::RestoreDefaults)->isHidden());
}

QTEST_MAIN(ViewerPluginExternalConfigureDialogTest)

#include "moc_viewerpluginexternalconfiguredialogtest.cpp"
