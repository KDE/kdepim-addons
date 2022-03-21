/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class GrammalecteGrammarErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteGrammarErrorTest(QObject *parent = nullptr);
    ~GrammalecteGrammarErrorTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldParseJson_data();
    void shouldParseJson();
};
