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
using namespace Qt::Literals::StringLiterals;

GravatarUpdateDialogTest::GravatarUpdateDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

GravatarUpdateDialogTest::~GravatarUpdateDialogTest() = default;

void GravatarUpdateDialogTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateDialog dlg;
    const auto w = dlg.findChild<KABGravatar::GravatarUpdateWidget *>(u"gravatarupdatewidget"_s);
    QVERIFY(w);

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    QVERIFY(!dlg.saveUrl());
}

QTEST_MAIN(GravatarUpdateDialogTest)

#include "moc_gravatarupdatedialogtest.cpp"
