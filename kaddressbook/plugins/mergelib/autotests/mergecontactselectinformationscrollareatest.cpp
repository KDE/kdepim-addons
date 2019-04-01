/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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

#include "mergecontactselectinformationscrollareatest.h"
#include <QTest>
#include "../widgets/mergecontactselectinformationwidget.h"
#include "../widgets/mergecontactselectinformationscrollarea.h"
#include "../widgets/mergecontactinfowidget.h"
#include <QScrollArea>
#include <QPushButton>
#include <QStackedWidget>

MergeContactSelectInformationScrollAreaTest::MergeContactSelectInformationScrollAreaTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationScrollAreaTest::~MergeContactSelectInformationScrollAreaTest()
{
}

void MergeContactSelectInformationScrollAreaTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationScrollArea w;
    QScrollArea *area = w.findChild<QScrollArea *>(QStringLiteral("scrollarea"));
    QVERIFY(area);
    QPushButton *mergeButton = w.findChild<QPushButton *>(QStringLiteral("merge"));
    QVERIFY(mergeButton);

    QStackedWidget *stackedwidget = w.findChild<QStackedWidget *>(QStringLiteral("stackwidget"));
    QVERIFY(stackedwidget);

    KABMergeContacts::MergeContactSelectInformationWidget *widget = w.findChild<KABMergeContacts::MergeContactSelectInformationWidget *>(QStringLiteral("selectinformationwidget"));
    QVERIFY(widget);

    for (int i = 0; i < stackedwidget->count(); ++i) {
        QWidget *w = stackedwidget->widget(i);
        const QString objName = w->objectName();
        bool hasCorrectName = (objName == QLatin1String("mergedcontactwidget")) || (objName == QLatin1String("selectwidget"));
        QVERIFY(hasCorrectName);
    }
    QCOMPARE(stackedwidget->currentWidget()->objectName(), QStringLiteral("selectwidget"));
}

QTEST_MAIN(MergeContactSelectInformationScrollAreaTest)
