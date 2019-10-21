/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimpolicywidgettest.h"
#include "dkimpolicywidget.h"
#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMPolicyWidgetTest)
DKIMPolicyWidgetTest::DKIMPolicyWidgetTest(QObject *parent)
    : QObject(parent)
{

}

DKIMPolicyWidgetTest::~DKIMPolicyWidgetTest()
{

}

void DKIMPolicyWidgetTest::shouldHaveDefaultValues()
{
    DKIMPolicyWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mVerifyIfEmailMustBeSigned = w.findChild<QCheckBox *>(QStringLiteral("mVerifyIfEmailMustBeSigned"));
    QVERIFY(mVerifyIfEmailMustBeSigned);
    QVERIFY(!mVerifyIfEmailMustBeSigned->text().isEmpty());
    QVERIFY(mVerifyIfEmailMustBeSigned->isEnabled());

    QCheckBox *mUseDMARC = w.findChild<QCheckBox *>QStringLiteral("mUseDMARC");
    QVERIFY(mUseDMARC);
    QVERIFY(!mUseDMARC->text().isEmpty());
    QVERIFY(!mUseDMARC->isEnabled());
}
