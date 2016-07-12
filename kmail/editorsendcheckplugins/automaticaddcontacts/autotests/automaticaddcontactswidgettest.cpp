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

#include "automaticaddcontactswidgettest.h"
#include "../automaticaddcontactsconfigurewidget.h"

#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>

AutomaticAddContactsWidgetTest::AutomaticAddContactsWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsWidgetTest::~AutomaticAddContactsWidgetTest()
{

}

void AutomaticAddContactsWidgetTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsWidget w;
    QVBoxLayout *vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    QCheckBox *mEnabled = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mEnabled);
    QVERIFY(!mEnabled->text().isEmpty());
    QVERIFY(!mEnabled->isChecked());

    QHBoxLayout *hlay = w.findChild<QHBoxLayout *>(QStringLiteral("folderlayout"));
    QVERIFY(hlay);
    QCOMPARE(hlay->margin(), 0);

}

void AutomaticAddContactsWidgetTest::shouldResetValue()
{
    AutomaticAddContactsWidget w;
    QCheckBox *mEnabled = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(!mEnabled->isChecked());
    mEnabled->setChecked(true);
    QVERIFY(mEnabled->isChecked());

    w.resetSettings();
    QVERIFY(!mEnabled->isChecked());
}

QTEST_MAIN(AutomaticAddContactsWidgetTest)
