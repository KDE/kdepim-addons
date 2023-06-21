/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresswidgettest.h"
#include "../confirmaddresswidget.h"
#include <QLabel>
#include <QListWidget>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressWidgetTest::ConfirmAddressWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressWidgetTest::~ConfirmAddressWidgetTest() = default;

void ConfirmAddressWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    QVERIFY(listEmails);
    QCOMPARE(listEmails->count(), 0);

    auto lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());
}

void ConfirmAddressWidgetTest::shouldAddAddress()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst{QStringLiteral("foo"), QStringLiteral("bla"), QStringLiteral("blo")};
    w.setValidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count());
}

void ConfirmAddressWidgetTest::shouldAddValidAndInvalidAddresses()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst{QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")};
    w.setValidAddresses(lst);
    w.setInvalidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count() * 2);
}

void ConfirmAddressWidgetTest::shouldHaveCheckableItem()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst{QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")};
    w.setValidAddresses(lst);
    for (int i = 0; i < listEmails->count(); ++i) {
        QListWidgetItem *item = listEmails->item(i);
        QCOMPARE(static_cast<bool>(item->flags() & Qt::ItemIsUserCheckable), false);
    }
    listEmails->clear();
    w.setInvalidAddresses(lst);
    for (int i = 0; i < listEmails->count(); ++i) {
        QListWidgetItem *item = listEmails->item(i);
        QCOMPARE(static_cast<bool>(item->flags() & Qt::ItemIsUserCheckable), true);
    }
}

void ConfirmAddressWidgetTest::shouldGetWhileListEmails()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList validLst{QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")};
    const QStringList invalidLst{QStringLiteral("boo"), QStringLiteral("boo2"), QStringLiteral("boo3")};
    w.setValidAddresses(validLst);
    w.setInvalidAddresses(invalidLst);
    for (int i = 0; i < listEmails->count(); ++i) {
        QListWidgetItem *item = listEmails->item(i);
        if (item->flags() & Qt::ItemIsUserCheckable) {
            item->setCheckState(Qt::Checked);
        }
    }
    QCOMPARE(w.whiteListSelectedEmails(), invalidLst);
}

QTEST_MAIN(ConfirmAddressWidgetTest)

#include "moc_confirmaddresswidgettest.cpp"
