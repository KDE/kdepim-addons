/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTMENUTEST_H
#define QUICKTEXTMENUTEST_H

#include <QObject>

class QuickTextMenuTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextMenuTest(QObject *parent = nullptr);
    ~QuickTextMenuTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // QUICKTEXTMENUTEST_H
