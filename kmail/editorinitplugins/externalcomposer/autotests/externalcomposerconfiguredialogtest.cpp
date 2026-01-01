/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfiguredialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../externalcomposerconfiguredialog.h"
#include "../externalcomposerconfigurewidget.h"
#include <QStandardPaths>
#include <QTest>

ExternalComposerConfigureDialogTest::ExternalComposerConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ExternalComposerConfigureDialogTest::shouldHaveDefaultValues()
{
    ExternalComposerConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    auto w = dlg.findChild<ExternalComposerConfigureWidget *>(u"configurewidget"_s);
    QVERIFY(w);
}

QTEST_MAIN(ExternalComposerConfigureDialogTest)

#include "moc_externalcomposerconfiguredialogtest.cpp"
