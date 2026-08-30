/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;

MergeContactSelectInformationScrollAreaTest::MergeContactSelectInformationScrollAreaTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationScrollAreaTest::~MergeContactSelectInformationScrollAreaTest() = default;

void MergeContactSelectInformationScrollAreaTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationScrollArea w;
    const auto area = w.findChild<QScrollArea *>(u"scrollarea"_s);
    QVERIFY(area);
    const auto mergeButton = w.findChild<QPushButton *>(u"merge"_s);
    QVERIFY(mergeButton);

    const auto stackedwidget = w.findChild<QStackedWidget *>(u"stackwidget"_s);
    QVERIFY(stackedwidget);

    const auto widget = w.findChild<KABMergeContacts::MergeContactSelectInformationWidget *>(u"selectinformationwidget"_s);
    QVERIFY(widget);

    for (int i = 0; i < stackedwidget->count(); ++i) {
        QWidget *widget2 = stackedwidget->widget(i);
        const QString objName = widget2->objectName();
        bool hasCorrectName = (objName == QLatin1StringView("mergedcontactwidget")) || (objName == QLatin1StringView("selectwidget"));
        QVERIFY(hasCorrectName);
    }
    QCOMPARE(stackedwidget->currentWidget()->objectName(), u"selectwidget"_s);
}

QTEST_MAIN(MergeContactSelectInformationScrollAreaTest)

#include "moc_mergecontactselectinformationscrollareatest.cpp"
