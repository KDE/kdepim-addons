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
GravatarUpdateWidgetTest::GravatarUpdateWidgetTest(QObject *parent)
    : QObject(parent)
{
}

GravatarUpdateWidgetTest::~GravatarUpdateWidgetTest() = default;

void GravatarUpdateWidgetTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateWidget widget;
    widget.show();
    const auto lab = widget.findChild<QLabel *>(QStringLiteral("emaillabel"));
    QVERIFY(lab);

    const auto emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));
    QVERIFY(emaillabel);

    const auto searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));
    QVERIFY(searchGravatar);
    QVERIFY(!searchGravatar->isEnabled());

    const auto resultGravatar = widget.findChild<QLabel *>(QStringLiteral("result"));
    QVERIFY(resultGravatar);

    QVERIFY(widget.pixmap().isNull());
    QVERIFY(widget.resolvedUrl().isEmpty());
}

void GravatarUpdateWidgetTest::shouldAffectEmail()
{
    KABGravatar::GravatarUpdateWidget widget;

    const auto emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));

    const auto searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));

    const QString newEmail(QStringLiteral("foo@kde.org"));
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
