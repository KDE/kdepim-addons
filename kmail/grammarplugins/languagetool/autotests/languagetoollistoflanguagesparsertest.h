/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLLISTOFLANGUAGESPARSERTEST_H
#define LANGUAGETOOLLISTOFLANGUAGESPARSERTEST_H

#include <QObject>

class LanguageToolListOfLanguagesParserTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolListOfLanguagesParserTest(QObject *parent = nullptr);
    ~LanguageToolListOfLanguagesParserTest() override = default;
};

#endif // LANGUAGETOOLLISTOFLANGUAGESPARSERTEST_H
