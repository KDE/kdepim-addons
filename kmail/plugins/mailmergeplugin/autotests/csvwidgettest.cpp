/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

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

CsvWidgetTest::~CsvWidgetTest() = default;

void CsvWidgetTest::shouldHaveDefaultValue()
{
    MailMerge::CsvWidget w;

    auto lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);

    auto urlrequester = w.findChild<KUrlRequester *>(QStringLiteral("cvsurlrequester"));
    QVERIFY(urlrequester);
    QVERIFY(urlrequester->url().isEmpty());
}

void CsvWidgetTest::shouldChangePath()
{
    MailMerge::CsvWidget w;

    auto urlrequester = w.findChild<KUrlRequester *>(QStringLiteral("cvsurlrequester"));
    QVERIFY(urlrequester->url().isEmpty());
    QUrl url(QStringLiteral("file:///tmp/foo.txt"));
    urlrequester->setUrl(url);
    QCOMPARE(urlrequester->url(), url);
}

QTEST_MAIN(CsvWidgetTest)

#include "moc_csvwidgettest.cpp"
