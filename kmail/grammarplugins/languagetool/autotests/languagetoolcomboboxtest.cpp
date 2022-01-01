/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolcomboboxtest.h"
#include "languagetoolcombobox.h"
#include <QTest>
QTEST_MAIN(LanguageToolComboBoxTest)
LanguageToolComboBoxTest::LanguageToolComboBoxTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolComboBoxTest::shouldHaveDefaultValue()
{
    LanguageToolComboBox w;
    QCOMPARE(w.count(), 30);
}
