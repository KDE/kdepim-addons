/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "confirmaddressconfigurewidgettest.h"
#include "../confirmaddressconfigurewidget.h"

#include <QTest>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <PimCommon/SimpleStringlistEditor>

ConfirmAddressConfigureWidgetTest::ConfirmAddressConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{

}

ConfirmAddressConfigureWidgetTest::~ConfirmAddressConfigureWidgetTest()
{

}

void ConfirmAddressConfigureWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureWidget w;

    QVBoxLayout *vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCheckBox *enable = w.findChild<QCheckBox *>(QStringLiteral("enable"));
    QVERIFY(enable);

    QGroupBox *groupBoxDomainName = w.findChild<QGroupBox *>(QStringLiteral("groupboxdomainname"));
    QVERIFY(groupBoxDomainName);
    QLayout *layoutDomainName = w.findChild<QVBoxLayout *>(QStringLiteral("layoutdomainname"));
    QVERIFY(layoutDomainName);
    PimCommon::SimpleStringListEditor *mDomainNameListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("domainnamelisteditor"));
    QVERIFY(mDomainNameListEditor);
}

QTEST_MAIN(ConfirmAddressConfigureWidgetTest)
