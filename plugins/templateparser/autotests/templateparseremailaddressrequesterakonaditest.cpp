/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateparseremailaddressrequesterakonaditest.h"
#include "../templateparseremailaddressrequesterakonadi.h"
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
#include <Akonadi/Contact/EmailAddressRequester>

TemplateParserEmailAddressRequesterAkonadiTest::TemplateParserEmailAddressRequesterAkonadiTest(QObject *parent)
    : QObject(parent)
{
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldHaveDefaultValues()
{
    TemplateParserEmailAddressRequesterAkonadi w;

    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    Akonadi::EmailAddressRequester *mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(QStringLiteral("EmailAddressRequester"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldAssignValue()
{
    TemplateParserEmailAddressRequesterAkonadi w;
    Akonadi::EmailAddressRequester *mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(QStringLiteral("EmailAddressRequester"));
    const QString str{
        QStringLiteral("foo")
    };
    w.setText(str);
    QCOMPARE(w.text(), str);
    QCOMPARE(mLineEdit->text(), str);
}

void TemplateParserEmailAddressRequesterAkonadiTest::shouldClearValue()
{
    TemplateParserEmailAddressRequesterAkonadi w;
    Akonadi::EmailAddressRequester *mLineEdit = w.findChild<Akonadi::EmailAddressRequester *>(QStringLiteral("EmailAddressRequester"));
    const QString str{
        QStringLiteral("foo")
    };
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
    w.setText(QStringLiteral("foo"));
    QCOMPARE(spy.size(), 1);
    w.clear();
    QCOMPARE(spy.size(), 2);
    w.setText(QStringLiteral("foo"));
    QCOMPARE(spy.size(), 3);
}

QTEST_MAIN(TemplateParserEmailAddressRequesterAkonadiTest)
