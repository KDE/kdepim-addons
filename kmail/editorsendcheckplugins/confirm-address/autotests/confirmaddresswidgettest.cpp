/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "confirmaddresswidgettest.h"
#include "../confirmaddresswidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QStandardPaths>

ConfirmAddressWidgetTest::ConfirmAddressWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressWidgetTest::~ConfirmAddressWidgetTest()
{
}

void ConfirmAddressWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->margin(), 0);

    QListWidget *listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    QVERIFY(listEmails);
    QCOMPARE(listEmails->count(), 0);

    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());
}

void ConfirmAddressWidgetTest::shouldAddAddress()
{
    ConfirmAddressWidget w;
    QListWidget *listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst {
        QStringLiteral("foo"), QStringLiteral("bla"), QStringLiteral("blo")
    };
    w.setValidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count());
}

void ConfirmAddressWidgetTest::shouldAddValidAndInvalidAddresses()
{
    ConfirmAddressWidget w;
    QListWidget *listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst {
        QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")
    };
    w.setValidAddresses(lst);
    w.setInvalidAddresses(lst);
    QCOMPARE(listEmails->count(), lst.count() * 2);
}

void ConfirmAddressWidgetTest::shouldHaveCheckableItem()
{
    ConfirmAddressWidget w;
    QListWidget *listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList lst {
        QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")
    };
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
    QListWidget *listEmails = w.findChild<QListWidget *>(QStringLiteral("listemails"));
    const QStringList validLst {
        QStringLiteral("foo"), QStringLiteral("foo"), QStringLiteral("foo")
    };
    const QStringList invalidLst {
        QStringLiteral("boo"), QStringLiteral("boo2"), QStringLiteral("boo3")
    };
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
