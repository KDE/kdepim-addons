/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactloseinformationwarningtest.h"
#include "../widgets/mergecontactloseinformationwarning.h"
#include <QAction>
#include <QSignalSpy>
#include <QTest>
#include <qtestmouse.h>
using namespace Qt::Literals::StringLiterals;

MergeContactLoseInformationWarningTest::MergeContactLoseInformationWarningTest(QObject *parent)
    : QObject(parent)
{
}

void MergeContactLoseInformationWarningTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactLoseInformationWarning w;
    QVERIFY(!w.isCloseButtonVisible());
    QVERIFY(!w.isVisible());
    const auto customize = w.findChild<QAction *>(u"customize"_s);
    QVERIFY(customize);
    const auto automatic = w.findChild<QAction *>(u"automatic"_s);
    QVERIFY(automatic);
}

void MergeContactLoseInformationWarningTest::shouldEmitSignals()
{
    KABMergeContacts::MergeContactLoseInformationWarning w;
    w.show();
    QVERIFY(QTest::qWaitForWindowExposed(&w));
    QVERIFY(w.isVisible());
    const auto customize = w.findChild<QAction *>(u"customize"_s);
    const auto automatic = w.findChild<QAction *>(u"automatic"_s);
    QSignalSpy spy1(&w, &KABMergeContacts::MergeContactLoseInformationWarning::continueMerging);
    QSignalSpy spy2(&w, &KABMergeContacts::MergeContactLoseInformationWarning::customizeMergingContacts);
    customize->trigger();
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);
    automatic->trigger();
    QCOMPARE(spy2.count(), 1);
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(MergeContactLoseInformationWarningTest)

#include "moc_mergecontactloseinformationwarningtest.cpp"
