/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLUPDATECOMBOBOXTEST_H
#define LANGUAGETOOLUPDATECOMBOBOXTEST_H

#include <QObject>

class LanguageToolUpdateComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolUpdateComboBoxTest(QObject *parent = nullptr);
    ~LanguageToolUpdateComboBoxTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // LANGUAGETOOLUPDATECOMBOBOXTEST_H
