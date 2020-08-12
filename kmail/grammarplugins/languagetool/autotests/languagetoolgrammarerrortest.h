/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLGRAMMARERRORTEST_H
#define LANGUAGETOOLGRAMMARERRORTEST_H

#include <QObject>

class LanguageToolGrammarErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGrammarErrorTest(QObject *parent = nullptr);
    ~LanguageToolGrammarErrorTest() = default;
private Q_SLOTS:
    void shouldParseJson_data();
    void shouldParseJson();
};

#endif // LANGUAGETOOLGRAMMARERRORTEST_H
