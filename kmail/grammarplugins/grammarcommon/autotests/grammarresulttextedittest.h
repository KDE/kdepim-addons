/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMARRESULTTEXTEDITTEST_H
#define GRAMMARRESULTTEXTEDITTEST_H

#include <QObject>

class GrammarResultTextEditTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultTextEditTest(QObject *parent = nullptr);
    ~GrammarResultTextEditTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAMMARRESULTTEXTEDITTEST_H
