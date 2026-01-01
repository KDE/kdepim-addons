/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../confirmaddressdialog.h"
#include "../confirmaddresswidget.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressDialogTest::ConfirmAddressDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressDialogTest::~ConfirmAddressDialogTest() = default;

void ConfirmAddressDialogTest::shouldHaveDefaultValue()
{
    ConfirmAddressDialog dlg;
    auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    auto confirmAddressWidget = dlg.findChild<ConfirmAddressWidget *>(u"confirmwidget"_s);
    QVERIFY(confirmAddressWidget);

    auto whiteListEmailsButton = dlg.findChild<QPushButton *>(u"whiteListEmailsButton"_s);
    QVERIFY(whiteListEmailsButton);
    QVERIFY(!whiteListEmailsButton->isEnabled());
}

QTEST_MAIN(ConfirmAddressDialogTest)

#include "moc_confirmaddressdialogtest.cpp"
