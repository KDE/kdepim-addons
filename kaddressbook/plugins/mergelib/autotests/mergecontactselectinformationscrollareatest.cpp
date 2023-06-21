/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationscrollareatest.h"
#include "../widgets/mergecontactinfowidget.h"
#include "../widgets/mergecontactselectinformationscrollarea.h"
#include "../widgets/mergecontactselectinformationwidget.h"
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTest>

MergeContactSelectInformationScrollAreaTest::MergeContactSelectInformationScrollAreaTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationScrollAreaTest::~MergeContactSelectInformationScrollAreaTest() = default;

void MergeContactSelectInformationScrollAreaTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationScrollArea w;
    auto area = w.findChild<QScrollArea *>(QStringLiteral("scrollarea"));
    QVERIFY(area);
    auto mergeButton = w.findChild<QPushButton *>(QStringLiteral("merge"));
    QVERIFY(mergeButton);

    auto stackedwidget = w.findChild<QStackedWidget *>(QStringLiteral("stackwidget"));
    QVERIFY(stackedwidget);

    auto widget = w.findChild<KABMergeContacts::MergeContactSelectInformationWidget *>(QStringLiteral("selectinformationwidget"));
    QVERIFY(widget);

    for (int i = 0; i < stackedwidget->count(); ++i) {
        QWidget *widget2 = stackedwidget->widget(i);
        const QString objName = widget2->objectName();
        bool hasCorrectName = (objName == QLatin1String("mergedcontactwidget")) || (objName == QLatin1String("selectwidget"));
        QVERIFY(hasCorrectName);
    }
    QCOMPARE(stackedwidget->currentWidget()->objectName(), QStringLiteral("selectwidget"));
}

QTEST_MAIN(MergeContactSelectInformationScrollAreaTest)

#include "moc_mergecontactselectinformationscrollareatest.cpp"
