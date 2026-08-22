/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingsdialogtest.h"
#include "../scamconfiguresettingsdialog.h"
#include "../scamconfiguresettingswidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ScamConfigureSettingsDialogTest)
ScamConfigureSettingsDialogTest::ScamConfigureSettingsDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void ScamConfigureSettingsDialogTest::shouldHaveDefaultValues()
{
    ScamConfigureSettingsDialog d;
    const auto mScamConfigureSettingsWidget = d.findChild<ScamConfigureSettingsWidget *>(QStringLiteral("mScamConfigureSettingsWidget"));
    QVERIFY(mScamConfigureSettingsWidget);

    const auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QVERIFY(!d.windowTitle().isEmpty());

    const auto buttonBox = d.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
}

#include "moc_scamconfiguresettingsdialogtest.cpp"
