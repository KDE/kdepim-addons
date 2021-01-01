/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "csvwidgettest.h"
#include "../widgets/csvwidget.h"
#include <KUrlRequester>
#include <QLabel>
#include <QTest>
CsvWidgetTest::CsvWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CsvWidgetTest::~CsvWidgetTest()
{
}

void CsvWidgetTest::shouldHaveDefaultValue()
{
    MailMerge::CsvWidget w;

    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);

    KUrlRequester *urlrequester = w.findChild<KUrlRequester *>(QStringLiteral("cvsurlrequester"));
    QVERIFY(urlrequester);
    QVERIFY(urlrequester->url().isEmpty());
}

void CsvWidgetTest::shouldChangePath()
{
    MailMerge::CsvWidget w;

    KUrlRequester *urlrequester = w.findChild<KUrlRequester *>(QStringLiteral("cvsurlrequester"));
    QVERIFY(urlrequester->url().isEmpty());
    QUrl url(QStringLiteral("file:///tmp/foo.txt"));
    urlrequester->setUrl(url);
    QCOMPARE(urlrequester->url(), url);
}

QTEST_MAIN(CsvWidgetTest)
