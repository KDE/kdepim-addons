/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateparseremailaddressrequesterakonaditest.h"
#include "../templateparseremailaddressrequesterakonadi.h"
#include <Akonadi/EmailAddressRequester>
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

TemplateParserEmailAddressRequesterAkonadiTest::TemplateParserEmailAddressRequesterAkonadiTest(QObject *parent)
    : QObject(parent)
{
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldHaveDefaultValues()
{
    TemplateParserEmailAddressRequesterAkonadi w;

    const auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(u"EmailAddressRequester"_s);
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldAssignValue()
{
    TemplateParserEmailAddressRequesterAkonadi w;
    const auto mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(u"EmailAddressRequester"_s);
    const QString str{u"foo"_s};
    w.setText(str);
    QCOMPARE(w.text(), str);
    QCOMPARE(mLineEdit->text(), str);
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldClearValue()
{
    TemplateParserEmailAddressRequesterAkonadi w;
    const auto mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(u"EmailAddressRequester"_s);
    const QString str{u"foo"_s};
    w.setText(str);
    QCOMPARE(w.text(), str);
    w.clear();
    QVERIFY(w.text().isEmpty());
    QVERIFY(mLineEdit->text().isEmpty());
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldEmitSignal()
{
    TemplateParserEmailAddressRequesterAkonadi w;
    QSignalSpy spy(&w, &TemplateParser::TemplateParserEmailAddressRequesterBase::textChanged);
    w.setText(u"foo"_s);
    QCOMPARE(spy.size(), 1);
    w.clear();
    QCOMPARE(spy.size(), 2);
    w.setText(u"foo"_s);
    QCOMPARE(spy.size(), 3);
}

QTEST_MAIN(TemplateParserEmailAddressRequesterAkonadiTest)

#include "moc_templateparseremailaddressrequesterakonaditest.cpp"
