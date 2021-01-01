/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef LANGUAGETOOLRESULTWIDGETTEST_H
#define LANGUAGETOOLRESULTWIDGETTEST_H

#include <QObject>

class LanguageToolResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolResultWidgetTest(QObject *parent = nullptr);
    ~LanguageToolResultWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // LANGUAGETOOLRESULTWIDGETTEST_H
