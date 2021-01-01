/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCONFIGWIDGETTEST_H
#define LANGUAGETOOLCONFIGWIDGETTEST_H

#include <QObject>

class LanguageToolConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolConfigWidgetTest(QObject *parent = nullptr);
    ~LanguageToolConfigWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldUpdateWidgets();
};

#endif // LANGUAGETOOLCONFIGWIDGETTEST_H
