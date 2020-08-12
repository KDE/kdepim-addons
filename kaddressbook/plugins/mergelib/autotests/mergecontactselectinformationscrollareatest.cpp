/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
