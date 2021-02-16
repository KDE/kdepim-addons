/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLGETLISTOFLANGUAGEJOBTEST_H
#define LANGUAGETOOLGETLISTOFLANGUAGEJOBTEST_H

#include <QObject>

class LanguageToolGetListOfLanguageJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGetListOfLanguageJobTest(QObject *parent = nullptr);
    ~LanguageToolGetListOfLanguageJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldBeAbleToStart();
};

#endif // LANGUAGETOOLGETLISTOFLANGUAGEJOBTEST_H
