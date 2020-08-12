/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCONFIGDIALOGTEST_H
#define LANGUAGETOOLCONFIGDIALOGTEST_H

#include <QObject>

class LanguageToolConfigDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolConfigDialogTest(QObject *parent = nullptr);
    ~LanguageToolConfigDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // LANGUAGETOOLCONFIGDIALOGTEST_H
