/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef LANGUAGETOOLPARSERTEST_H
#define LANGUAGETOOLPARSERTEST_H

#include <QObject>

class LanguageToolParserTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolParserTest(QObject *parent = nullptr);
    ~LanguageToolParserTest() = default;
private Q_SLOTS:
    void shouldParseJson();
    void shouldParseJson_data();
};

#endif // LANGUAGETOOLPARSERTEST_H
