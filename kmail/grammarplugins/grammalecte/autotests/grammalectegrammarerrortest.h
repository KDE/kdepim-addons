/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAMMALECTEINFOTEST_H
#define GRAMMALECTEINFOTEST_H

#include <QObject>

class GrammalecteGrammarErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteGrammarErrorTest(QObject *parent = nullptr);
    ~GrammalecteGrammarErrorTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldParseJson_data();
    void shouldParseJson();
};

#endif // GRAMMALECTEINFOTEST_H
