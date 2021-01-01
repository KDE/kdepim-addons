/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTWIDGETTEST_H
#define QUICKTEXTWIDGETTEST_H

#include <QObject>

class QuickTextWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextWidgetTest(QObject *parent = nullptr);
    ~QuickTextWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // QUICKTEXTWIDGETTEST_H
