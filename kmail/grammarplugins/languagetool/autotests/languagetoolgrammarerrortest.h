/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LanguageToolGrammarErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGrammarErrorTest(QObject *parent = nullptr);
    ~LanguageToolGrammarErrorTest() override = default;
private Q_SLOTS:
    void shouldParseJson_data();
    void shouldParseJson();
};
