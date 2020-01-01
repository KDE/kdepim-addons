/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#include "languagetoolconfigdialogtest.h"
#include "languagetoolconfigdialog.h"
#include "languagetoolconfigwidget.h"
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QTest>
#include <QDialogButtonBox>
QTEST_MAIN(LanguageToolConfigDialogTest)
LanguageToolConfigDialogTest::LanguageToolConfigDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolConfigDialogTest::shouldHaveDefaultValue()
{
    LanguageToolConfigDialog w(nullptr);
    QVERIFY(!w.windowTitle().isEmpty());

    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    LanguageToolConfigWidget *mConfigWidget = w.findChild<LanguageToolConfigWidget *>(QStringLiteral("configwidget"));
    QVERIFY(mConfigWidget);

    QDialogButtonBox *box = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(box);
}
