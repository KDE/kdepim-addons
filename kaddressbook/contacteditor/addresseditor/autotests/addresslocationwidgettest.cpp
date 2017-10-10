/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "addresslocationwidgettest.h"
#include "../addresslocationwidget.h"
#include <QLabel>
#include <QPushButton>
#include <KComboBox>
#include <KLineEdit>
#include <QTest>
#include <QCheckBox>
#include <editor/addresseditor/selectaddresstypecombobox.h>
using namespace ContactEditor;
AddressLocationWidgetTest::AddressLocationWidgetTest(QObject *parent)
    : QObject(parent)
{
}

AddressLocationWidgetTest::~AddressLocationWidgetTest()
{
}

void AddressLocationWidgetTest::shouldHaveDefaultValue()
{
    AddressLocationWidget w;

    SelectAddressTypeComboBox *typeAddress = w.findChild<SelectAddressTypeComboBox *>(QStringLiteral("typeaddress"));
    QVERIFY(typeAddress);

    QLabel *streetlabel = w.findChild<QLabel *>(QStringLiteral("streetlabel"));
    QVERIFY(streetlabel);
    KLineEdit *mStreetEdit = w.findChild<KLineEdit *>(QStringLiteral("streetlineedit"));
    QVERIFY(mStreetEdit);

    QLabel *postofficeboxlabel = w.findChild<QLabel *>(QStringLiteral("postofficeboxlabel"));
    QVERIFY(postofficeboxlabel);
    KLineEdit *postofficeboxlineedit = w.findChild<KLineEdit *>(QStringLiteral("postofficeboxlineedit"));
    QVERIFY(postofficeboxlineedit);

    QLabel *localitylabel = w.findChild<QLabel *>(QStringLiteral("localitylabel"));
    QVERIFY(localitylabel);
    KLineEdit *localitylineedit = w.findChild<KLineEdit *>(QStringLiteral("localitylineedit"));
    QVERIFY(localitylineedit);

    QLabel *regionlabel = w.findChild<QLabel *>(QStringLiteral("regionlabel"));
    QVERIFY(regionlabel);
    KLineEdit *regionlineedit = w.findChild<KLineEdit *>(QStringLiteral("regionlineedit"));
    QVERIFY(regionlineedit);

    QLabel *postalcodelabel = w.findChild<QLabel *>(QStringLiteral("postalcodelabel"));
    QVERIFY(postalcodelabel);
    KLineEdit *postalcodelineedit = w.findChild<KLineEdit *>(QStringLiteral("postalcodelineedit"));
    QVERIFY(postalcodelineedit);

    QLabel *countrylabel = w.findChild<QLabel *>(QStringLiteral("countrylabel"));
    QVERIFY(countrylabel);
    KComboBox *countrycombobox = w.findChild<KComboBox *>(QStringLiteral("countrycombobox"));
    QVERIFY(countrycombobox);

    QCheckBox *preferredcheckbox = w.findChild<QCheckBox *>(QStringLiteral("preferredcheckbox"));
    QVERIFY(preferredcheckbox);

    QPushButton *addbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("addbuttonaddress"));
    QVERIFY(addbuttonaddress);

    QPushButton *modifybuttonaddress = w.findChild<QPushButton *>(QStringLiteral("modifybuttonaddress"));
    QVERIFY(modifybuttonaddress);

    QPushButton *cancelbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("cancelbuttonaddress"));
    QVERIFY(cancelbuttonaddress);
}

void AddressLocationWidgetTest::shouldChangeReadOnlyStatus()
{
    AddressLocationWidget w;

    w.setReadOnly(true);
    SelectAddressTypeComboBox *typeAddress = w.findChild<SelectAddressTypeComboBox *>(QStringLiteral("typeaddress"));
    QCOMPARE(typeAddress->isEnabled(), false);
    KLineEdit *mStreetEdit = w.findChild<KLineEdit *>(QStringLiteral("streetlineedit"));
    QCOMPARE(mStreetEdit->isReadOnly(), true);
    KLineEdit *postofficeboxlineedit = w.findChild<KLineEdit *>(QStringLiteral("postofficeboxlineedit"));
    QCOMPARE(postofficeboxlineedit->isReadOnly(), true);
    KLineEdit *localitylineedit = w.findChild<KLineEdit *>(QStringLiteral("localitylineedit"));
    QCOMPARE(localitylineedit->isReadOnly(), true);
    KLineEdit *regionlineedit = w.findChild<KLineEdit *>(QStringLiteral("regionlineedit"));
    QCOMPARE(regionlineedit->isReadOnly(), true);
    KLineEdit *postalcodelineedit = w.findChild<KLineEdit *>(QStringLiteral("postalcodelineedit"));
    QCOMPARE(postalcodelineedit->isReadOnly(), true);
    KComboBox *countrycombobox = w.findChild<KComboBox *>(QStringLiteral("countrycombobox"));
    QCOMPARE(countrycombobox->isEnabled(), false);
    QCheckBox *preferredcheckbox = w.findChild<QCheckBox *>(QStringLiteral("preferredcheckbox"));
    QCOMPARE(preferredcheckbox->isEnabled(), false);
    QPushButton *addbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("addbuttonaddress"));
    QCOMPARE(addbuttonaddress->isEnabled(), false);
    QPushButton *modifybuttonaddress = w.findChild<QPushButton *>(QStringLiteral("modifybuttonaddress"));
    QCOMPARE(modifybuttonaddress->isEnabled(), false);
    QPushButton *cancelbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("cancelbuttonaddress"));
    QCOMPARE(cancelbuttonaddress->isEnabled(), false);
}

QTEST_MAIN(AddressLocationWidgetTest)
