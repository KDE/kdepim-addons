/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCOMBOBOXTEST_H
#define LANGUAGETOOLCOMBOBOXTEST_H

#include <QObject>

class LanguageToolComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolComboBoxTest(QObject *parent = nullptr);
    ~LanguageToolComboBoxTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // LANGUAGETOOLCOMBOBOXTEST_H
