/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfiguredialogtest.h"
#include "../externalcomposerconfiguredialog.h"
#include "../externalcomposerconfigurewidget.h"
#include <QTest>
#include <QStandardPaths>

ExternalComposerConfigureDialogTest::ExternalComposerConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ExternalComposerConfigureDialogTest::shouldHaveDefaultValues()
{
    ExternalComposerConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    ExternalComposerConfigureWidget *w = dlg.findChild<ExternalComposerConfigureWidget *>(QStringLiteral("configurewidget"));
    QVERIFY(w);
}

QTEST_MAIN(ExternalComposerConfigureDialogTest)
