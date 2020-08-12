/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMARRESULTJOBTEST_H
#define GRAMMARRESULTJOBTEST_H

#include <QObject>

class GrammarResultJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultJobTest(QObject *parent = nullptr);
    ~GrammarResultJobTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};

#endif // GRAMMARRESULTJOBTEST_H
