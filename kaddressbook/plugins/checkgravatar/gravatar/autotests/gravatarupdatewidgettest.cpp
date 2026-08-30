/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatewidgettest.h"
#include "../gravatar/widgets/gravatarupdatewidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
GravatarUpdateWidgetTest::GravatarUpdateWidgetTest(QObject *parent)
    : QObject(parent)
{
}

GravatarUpdateWidgetTest::~GravatarUpdateWidgetTest() = default;

void GravatarUpdateWidgetTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateWidget widget;
    widget.show();
    const auto lab = widget.findChild<QLabel *>(u"emaillabel"_s);
    QVERIFY(lab);

    const auto emaillabel = widget.findChild<QLabel *>(u"email"_s);
    QVERIFY(emaillabel);

    const auto searchGravatar = widget.findChild<QPushButton *>(u"search"_s);
    QVERIFY(searchGravatar);
    QVERIFY(!searchGravatar->isEnabled());

    const auto resultGravatar = widget.findChild<QLabel *>(u"result"_s);
    QVERIFY(resultGravatar);

    QVERIFY(widget.pixmap().isNull());
    QVERIFY(widget.resolvedUrl().isEmpty());
}

void GravatarUpdateWidgetTest::shouldAffectEmail()
{
    KABGravatar::GravatarUpdateWidget widget;

    const auto emaillabel = widget.findChild<QLabel *>(u"email"_s);

    const auto searchGravatar = widget.findChild<QPushButton *>(u"search"_s);

    const QString newEmail(u"foo@kde.org"_s);
    widget.setEmail(newEmail);

    QCOMPARE(emaillabel->text(), newEmail);
    QVERIFY(searchGravatar->isEnabled());

    QString cleanName;
    widget.setEmail(cleanName);
    QCOMPARE(emaillabel->text(), cleanName);
    QVERIFY(!searchGravatar->isEnabled());
}

QTEST_MAIN(GravatarUpdateWidgetTest)

#include "moc_gravatarupdatewidgettest.cpp"
