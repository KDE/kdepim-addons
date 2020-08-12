/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTEGENERATECONFIGOPTIONJOBTEST_H
#define GRAMMALECTEGENERATECONFIGOPTIONJOBTEST_H

#include <QObject>

class GrammalecteGenerateConfigOptionJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteGenerateConfigOptionJobTest(QObject *parent = nullptr);
    ~GrammalecteGenerateConfigOptionJobTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};

#endif // GRAMMALECTEGENERATECONFIGOPTIONJOBTEST_H
