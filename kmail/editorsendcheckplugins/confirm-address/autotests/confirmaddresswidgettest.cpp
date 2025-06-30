/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresswidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto listEmails = w.findChild<QListWidget *>(u"listemails"_s);
    QVERIFY(listEmails);
    QCOMPARE(listEmails->count(), 0);

    auto lab = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());
}

void ConfirmAddressWidgetTest::shouldAddAddress()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(u"listemails"_s);
    const QStringList lst{u"foo"_s, u"bla"_s, QStringLiteral("blo")};
    w.setValidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count());
}

void ConfirmAddressWidgetTest::shouldAddValidAndInvalidAddresses()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(u"listemails"_s);
    const QStringList lst{u"foo"_s, u"foo"_s, QStringLiteral("foo")};
    w.setValidAddresses(lst);
    w.setInvalidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count() * 2);
}

void ConfirmAddressWidgetTest::shouldHaveCheckableItem()
{
    ConfirmAddressWidget w;
    auto listEmails = w.findChild<QListWidget *>(u"listemails"_s);
    const QStringList lst{u"foo"_s, u"foo"_s, QStringLiteral("foo")};
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
    auto listEmails = w.findChild<QListWidget *>(u"listemails"_s);
    const QStringList validLst{u"foo"_s, u"foo"_s, QStringLiteral("foo")};
    const QStringList invalidLst{u"boo"_s, u"boo2"_s, QStringLiteral("boo3")};
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
