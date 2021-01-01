/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigdialogtest.h"
#include "grammalecteconfigdialog.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
#include <grammalecteconfigwidget.h>
QTEST_MAIN(GrammalecteConfigDialogTest)
GrammalecteConfigDialogTest::GrammalecteConfigDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteConfigDialogTest::shouldHaveDefaultValue()
{
    GrammalecteConfigDialog w(nullptr, true);
    QVERIFY(!w.windowTitle().isEmpty());

    auto *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto *mConfigWidget = w.findChild<GrammalecteConfigWidget *>(QStringLiteral("configwidget"));
    QVERIFY(mConfigWidget);

    auto *box = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(box);
}
