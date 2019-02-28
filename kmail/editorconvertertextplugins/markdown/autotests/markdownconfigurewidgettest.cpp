/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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

#include "markdownconfigurewidgettest.h"
#include "../markdownconfigurewidget.h"
#include "kdepimtest_layout.h"
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QTest>

QTEST_MAIN(MarkdownConfigureWidgetTest)
MarkdownConfigureWidgetTest::MarkdownConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownConfigureWidgetTest::shouldHaveDefaultValue()
{
    MarkdownConfigureWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    KdepimTestLayout::checkContentsMargins(0, mainLayout);

    QCheckBox *mLatexSupport = w.findChild<QCheckBox *>(QStringLiteral("latex"));
    QVERIFY(mLatexSupport);
    QVERIFY(!mLatexSupport->text().isEmpty());

    QCheckBox *mExtraDefinitionLists = w.findChild<QCheckBox *>(QStringLiteral("extradefinitionlists"));
    QVERIFY(mExtraDefinitionLists);
    QVERIFY(!mExtraDefinitionLists->text().isEmpty());
}
