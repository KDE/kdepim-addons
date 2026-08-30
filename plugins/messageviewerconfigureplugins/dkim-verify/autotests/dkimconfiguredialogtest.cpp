/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguredialogtest.h"
#include "../dkimconfiguredialog.h"
#include "../dkimconfigurewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(DKIMConfigureDialogTest)

DKIMConfigureDialogTest::DKIMConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMConfigureDialogTest::shouldHaveDefaultValue()
{
    DKIMConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    const auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    const auto mConfigureWidget = dlg.findChild<DKIMConfigureWidget *>(u"mConfigureWidget"_s);
    QVERIFY(mConfigureWidget);

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(),
             QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults});
}

#include "moc_dkimconfiguredialogtest.cpp"
