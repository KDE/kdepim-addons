/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactloseinformationwarningtest.h"
#include "../widgets/mergecontactloseinformationwarning.h"
#include <QAction>
#include <QSignalSpy>
#include <QTest>
#include <qtestmouse.h>

MergeContactLoseInformationWarningTest::MergeContactLoseInformationWarningTest(QObject *parent)
    : QObject(parent)
{
    if (qEnvironmentVariableIntValue("KDECI_CANNOT_CREATE_WINDOWS")) {
        QSKIP("KDE CI can't create a window on this platform, skipping some gui tests");
    }
}

void MergeContactLoseInformationWarningTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactLoseInformationWarning w;
    QVERIFY(!w.isCloseButtonVisible());
    QVERIFY(!w.isVisible());
    auto customize = w.findChild<QAction *>(QStringLiteral("customize"));
    QVERIFY(customize);
    auto automatic = w.findChild<QAction *>(QStringLiteral("automatic"));
    QVERIFY(automatic);
}

void MergeContactLoseInformationWarningTest::shouldEmitSignals()
{
    KABMergeContacts::MergeContactLoseInformationWarning w;
    w.show();
    QVERIFY(QTest::qWaitForWindowExposed(&w));
    QVERIFY(w.isVisible());
    auto customize = w.findChild<QAction *>(QStringLiteral("customize"));
    auto automatic = w.findChild<QAction *>(QStringLiteral("automatic"));
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
