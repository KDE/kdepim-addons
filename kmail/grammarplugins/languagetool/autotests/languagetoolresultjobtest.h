/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLRESULTJOBTEST_H
#define LANGUAGETOOLRESULTJOBTEST_H

#include <QObject>

class LanguageToolResultJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolResultJobTest(QObject *parent = nullptr);
    ~LanguageToolResultJobTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};

#endif // LANGUAGETOOLRESULTJOBTEST_H
