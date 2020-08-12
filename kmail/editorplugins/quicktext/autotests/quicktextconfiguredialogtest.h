/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTCONFIGUREDIALOGTEST_H
#define QUICKTEXTCONFIGUREDIALOGTEST_H

#include <QObject>

class QuickTextConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextConfigureDialogTest(QObject *parent = nullptr);
    ~QuickTextConfigureDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // QUICKTEXTCONFIGUREDIALOGTEST_H
