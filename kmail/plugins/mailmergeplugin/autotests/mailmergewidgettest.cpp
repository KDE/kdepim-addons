/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergewidgettest.h"
#include "../widgets/mailmergewidget.h"
#include <PimCommon/SimpleStringListEditor>
#include <QTest>
#include <QComboBox>
#include <QStackedWidget>
#include <QSignalSpy>
using namespace MailMerge;
Q_DECLARE_METATYPE(MailMerge::MailMergeWidget::SourceType)
MailMergeWidgetTest::MailMergeWidgetTest()
{
    qRegisterMetaType<MailMergeWidget::SourceType>();
}

void MailMergeWidgetTest::shouldHaveDefaultValueOnCreation()
{
    MailMergeWidget mailmerge;
    QComboBox *source = mailmerge.findChild<QComboBox *>(QStringLiteral("source"));
    QVERIFY(source);
    QCOMPARE(source->currentIndex(), 0);

    QStackedWidget *stackedwidget = mailmerge.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedwidget);
    QCOMPARE(stackedwidget->count(), 2);
    QCOMPARE(stackedwidget->currentIndex(), 0);

    for (int i = 0; i < stackedwidget->count(); ++i) {
        const QString objectName = stackedwidget->widget(i)->objectName();
        bool hasName = (objectName == QLatin1String("addressbookwidget")
                        || objectName == QLatin1String("csvwidget"));
        QVERIFY(hasName);
    }
    PimCommon::SimpleStringListEditor *listEditor = mailmerge.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("attachment-list"));
    QVERIFY(listEditor);
    QCOMPARE(listEditor->stringList().count(), 0);
}

void MailMergeWidgetTest::shouldEmitSourceModeChanged()
{
    MailMergeWidget mailmerge;
    QComboBox *source = mailmerge.findChild<QComboBox *>(QStringLiteral("source"));
    QCOMPARE(source->currentIndex(), 0);
    QSignalSpy spy(&mailmerge, SIGNAL(sourceModeChanged(MailMerge::MailMergeWidget::SourceType)));
    source->setCurrentIndex(1);
    QCOMPARE(spy.count(), 1);
}

void MailMergeWidgetTest::shouldDontEmitSourceModeChangedWhenIndexIsInvalid()
{
    MailMergeWidget mailmerge;
    QComboBox *source = mailmerge.findChild<QComboBox *>(QStringLiteral("source"));
    QCOMPARE(source->currentIndex(), 0);
    QSignalSpy spy(&mailmerge, SIGNAL(sourceModeChanged(MailMerge::MailMergeWidget::SourceType)));
    source->setCurrentIndex(-1);
    QCOMPARE(spy.count(), 0);
}

void MailMergeWidgetTest::shouldChangeStackedWidgetIndexWhenChangeComboboxIndex()
{
    MailMergeWidget mailmerge;
    QComboBox *source = mailmerge.findChild<QComboBox *>(QStringLiteral("source"));
    QCOMPARE(source->currentIndex(), 0);

    QStackedWidget *stackedwidget = mailmerge.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QCOMPARE(stackedwidget->currentIndex(), 0);
    source->setCurrentIndex(0);
    QCOMPARE(stackedwidget->currentIndex(), 0);
    source->setCurrentIndex(1);
    QCOMPARE(stackedwidget->currentIndex(), 1);
}

QTEST_MAIN(MailMergeWidgetTest)
