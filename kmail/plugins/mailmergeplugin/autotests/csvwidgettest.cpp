/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "csvwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto lab = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);

    auto urlrequester = w.findChild<KUrlRequester *>(u"cvsurlrequester"_s);
    QVERIFY(urlrequester);
    QVERIFY(urlrequester->url().isEmpty());
}

void CsvWidgetTest::shouldChangePath()
{
    MailMerge::CsvWidget w;

    auto urlrequester = w.findChild<KUrlRequester *>(u"cvsurlrequester"_s);
    QVERIFY(urlrequester->url().isEmpty());
    QUrl url(u"file:///tmp/foo.txt"_s);
    urlrequester->setUrl(url);
    QCOMPARE(urlrequester->url(), url);
}

QTEST_MAIN(CsvWidgetTest)

#include "moc_csvwidgettest.cpp"
