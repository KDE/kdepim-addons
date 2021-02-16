/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAMMARRESULTWIDGETTEST_H
#define GRAMMARRESULTWIDGETTEST_H

#include <QObject>

class GrammarResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultWidgetTest(QObject *parent = nullptr);
    ~GrammarResultWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAMMARRESULTWIDGETTEST_H
