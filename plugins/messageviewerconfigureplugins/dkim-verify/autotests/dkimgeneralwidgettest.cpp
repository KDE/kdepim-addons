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

#include "dkimgeneralwidgettest.h"
#include "dkimgeneralwidget.h"
#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMGeneralWidgetTest)
DKIMGeneralWidgetTest::DKIMGeneralWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMGeneralWidgetTest::shouldHaveDefaultValues()
{
    DKIMGeneralWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mEnableDkimSupport = w.findChild<QCheckBox *>(QStringLiteral("enableDkimSupport"));
    QVERIFY(mEnableDkimSupport);
    QVERIFY(!mEnableDkimSupport->text().isEmpty());
    QVERIFY(!mEnableDkimSupport->isChecked());

    QCheckBox *mSaveResult = w.findChild<QCheckBox *>(QStringLiteral("mSaveResult"));
    QVERIFY(mSaveResult);
    QVERIFY(!mSaveResult->text().isEmpty());
    QVERIFY(!mSaveResult->isChecked());

    QCheckBox *mSaveKey = w.findChild<QCheckBox *>(QStringLiteral("mSaveKey"));
    QVERIFY(mSaveKey);
    QVERIFY(!mSaveKey->text().isEmpty());
    QVERIFY(!mSaveKey->isChecked());
}
