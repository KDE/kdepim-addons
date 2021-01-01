/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialogtest.h"
#include "languagetoolconfigdialog.h"
#include "languagetoolconfigwidget.h"
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QTest>
#include <QDialogButtonBox>
QTEST_MAIN(LanguageToolConfigDialogTest)
LanguageToolConfigDialogTest::LanguageToolConfigDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolConfigDialogTest::shouldHaveDefaultValue()
{
    LanguageToolConfigDialog w(nullptr);
    QVERIFY(!w.windowTitle().isEmpty());

    auto *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto *mConfigWidget = w.findChild<LanguageToolConfigWidget *>(QStringLiteral("configwidget"));
    QVERIFY(mConfigWidget);

    auto *box = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(box);
}
