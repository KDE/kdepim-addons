/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolupdatecomboboxtest.h"
#include "languagetoolupdatecombobox.h"
#include <QTest>
QTEST_MAIN(LanguageToolUpdateComboBoxTest)

LanguageToolUpdateComboBoxTest::LanguageToolUpdateComboBoxTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolUpdateComboBoxTest::shouldHaveDefaultValues()
{
    LanguageToolUpdateComboBox w;
    QVERIFY(!w.languageToolCombobox());
    QVERIFY(!w.parentWidget());
}
