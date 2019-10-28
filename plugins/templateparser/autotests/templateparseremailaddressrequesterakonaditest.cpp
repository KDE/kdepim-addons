/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
