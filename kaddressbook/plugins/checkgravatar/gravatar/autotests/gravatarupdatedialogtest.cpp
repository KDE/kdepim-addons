/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatedialogtest.h"
#include "../widgets/gravatarupdatedialog.h"
#include "../widgets/gravatarupdatewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>

GravatarUpdateDialogTest::GravatarUpdateDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

GravatarUpdateDialogTest::~GravatarUpdateDialogTest() = default;

void GravatarUpdateDialogTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateDialog dlg;
    auto w = dlg.findChild<KABGravatar::GravatarUpdateWidget *>(QStringLiteral("gravatarupdatewidget"));
    QVERIFY(w);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(!dlg.saveUrl());
}

QTEST_MAIN(GravatarUpdateDialogTest)

#include "moc_gravatarupdatedialogtest.cpp"
