/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressdialogtest.h"
#include "../confirmaddressdialog.h"
#include "../confirmaddresswidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>

ConfirmAddressDialogTest::ConfirmAddressDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressDialogTest::~ConfirmAddressDialogTest()
{
}

void ConfirmAddressDialogTest::shouldHaveDefaultValue()
{
    ConfirmAddressDialog dlg;
    QVBoxLayout *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    QDialogButtonBox *buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    ConfirmAddressWidget *confirmAddressWidget = dlg.findChild<ConfirmAddressWidget *>(QStringLiteral("confirmwidget"));
    QVERIFY(confirmAddressWidget);

    QPushButton *whiteListEmailsButton = dlg.findChild<QPushButton *>(QStringLiteral("whiteListEmailsButton"));
    QVERIFY(whiteListEmailsButton);
    QVERIFY(!whiteListEmailsButton->isEnabled());
}

QTEST_MAIN(ConfirmAddressDialogTest)
