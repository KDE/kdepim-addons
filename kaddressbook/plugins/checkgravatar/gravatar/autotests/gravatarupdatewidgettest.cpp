/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

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
    auto lab = widget.findChild<QLabel *>(QStringLiteral("emaillabel"));
    QVERIFY(lab);

    auto emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));
    QVERIFY(emaillabel);

    auto useLibravatar = widget.findChild<QCheckBox *>(QStringLiteral("uselibravatar"));
    QVERIFY(useLibravatar);
    QVERIFY(!useLibravatar->isChecked());
    QVERIFY(useLibravatar->isEnabled());

    auto useFallbackGravatar = widget.findChild<QCheckBox *>(QStringLiteral("fallbackgravatar"));
    QVERIFY(useFallbackGravatar);
    QVERIFY(!useFallbackGravatar->isChecked());
    QVERIFY(!useFallbackGravatar->isEnabled());

    auto searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));
    QVERIFY(searchGravatar);
    QVERIFY(!searchGravatar->isEnabled());

    auto resultGravatar = widget.findChild<QLabel *>(QStringLiteral("result"));
    QVERIFY(resultGravatar);

    QVERIFY(widget.pixmap().isNull());
    QVERIFY(widget.resolvedUrl().isEmpty());
}

void GravatarUpdateWidgetTest::shouldAffectEmail()
{
    KABGravatar::GravatarUpdateWidget widget;

    auto emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));

    auto searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));

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
