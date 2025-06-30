/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../widgets/mailmergewidget.h"
#include <PimCommon/SimpleStringListEditor>
#include <QComboBox>
#include <QSignalSpy>
#include <QStackedWidget>
#include <QTest>
using namespace MailMerge;
Q_DECLARE_METATYPE(MailMerge::MailMergeWidget::SourceType)
MailMergeWidgetTest::MailMergeWidgetTest()
{
    qRegisterMetaType<MailMergeWidget::SourceType>();
}

void MailMergeWidgetTest::shouldHaveDefaultValueOnCreation()
{
    MailMergeWidget mailmerge;
    auto source = mailmerge.findChild<QComboBox *>(u"source"_s);
    QVERIFY(source);
    QCOMPARE(source->currentIndex(), 0);

    auto stackedwidget = mailmerge.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(stackedwidget);
    QCOMPARE(stackedwidget->count(), 2);
    QCOMPARE(stackedwidget->currentIndex(), 0);

    for (int i = 0; i < stackedwidget->count(); ++i) {
        const QString objectName = stackedwidget->widget(i)->objectName();
        bool hasName = (objectName == QLatin1StringView("addressbookwidget") || objectName == QLatin1StringView("csvwidget"));
        QVERIFY(hasName);
    }
    auto listEditor = mailmerge.findChild<PimCommon::SimpleStringListEditor *>(u"attachment-list"_s);
    QVERIFY(listEditor);
    QCOMPARE(listEditor->stringList().count(), 0);
}

void MailMergeWidgetTest::shouldEmitSourceModeChanged()
{
    MailMergeWidget mailmerge;
    auto source = mailmerge.findChild<QComboBox *>(u"source"_s);
    QCOMPARE(source->currentIndex(), 0);
    QSignalSpy spy(&mailmerge, &MailMergeWidget::sourceModeChanged);
    source->setCurrentIndex(1);
    QCOMPARE(spy.count(), 1);
}

void MailMergeWidgetTest::shouldDontEmitSourceModeChangedWhenIndexIsInvalid()
{
    MailMergeWidget mailmerge;
    auto source = mailmerge.findChild<QComboBox *>(u"source"_s);
    QCOMPARE(source->currentIndex(), 0);
    QSignalSpy spy(&mailmerge, &MailMergeWidget::sourceModeChanged);
    source->setCurrentIndex(-1);
    QCOMPARE(spy.count(), 0);
}

void MailMergeWidgetTest::shouldChangeStackedWidgetIndexWhenChangeComboboxIndex()
{
    MailMergeWidget mailmerge;
    auto source = mailmerge.findChild<QComboBox *>(u"source"_s);
    QCOMPARE(source->currentIndex(), 0);

    auto stackedwidget = mailmerge.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QCOMPARE(stackedwidget->currentIndex(), 0);
    source->setCurrentIndex(0);
    QCOMPARE(stackedwidget->currentIndex(), 0);
    source->setCurrentIndex(1);
    QCOMPARE(stackedwidget->currentIndex(), 1);
}

QTEST_MAIN(MailMergeWidgetTest)

#include "moc_mailmergewidgettest.cpp"
