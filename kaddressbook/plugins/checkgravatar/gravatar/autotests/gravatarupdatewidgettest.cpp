/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatewidgettest.h"
#include <QTest>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include "../gravatar/widgets/gravatarupdatewidget.h"
GravatarUpdateWidgetTest::GravatarUpdateWidgetTest(QObject *parent)
    : QObject(parent)
{
}

GravatarUpdateWidgetTest::~GravatarUpdateWidgetTest()
{
}

void GravatarUpdateWidgetTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateWidget widget;
    widget.show();
    QLabel *lab = widget.findChild<QLabel *>(QStringLiteral("emaillabel"));
    QVERIFY(lab);

    QLabel *emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));
    QVERIFY(emaillabel);

    QCheckBox *useLibravatar = widget.findChild<QCheckBox *>(QStringLiteral("uselibravatar"));
    QVERIFY(useLibravatar);
    QVERIFY(!useLibravatar->isChecked());
    QVERIFY(useLibravatar->isEnabled());

    QCheckBox *useFallbackGravatar = widget.findChild<QCheckBox *>(QStringLiteral("fallbackgravatar"));
    QVERIFY(useFallbackGravatar);
    QVERIFY(!useFallbackGravatar->isChecked());
    QVERIFY(!useFallbackGravatar->isEnabled());

    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));
    QVERIFY(searchGravatar);
    QVERIFY(!searchGravatar->isEnabled());

    QLabel *resultGravatar = widget.findChild<QLabel *>(QStringLiteral("result"));
    QVERIFY(resultGravatar);

    QVERIFY(widget.pixmap().isNull());
    QVERIFY(widget.resolvedUrl().isEmpty());
}

void GravatarUpdateWidgetTest::shouldAffectEmail()
{
    KABGravatar::GravatarUpdateWidget widget;

    QLabel *emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));

    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));

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
