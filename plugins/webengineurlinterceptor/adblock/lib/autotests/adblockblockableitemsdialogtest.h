/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKBLOCKABLEITEMSDIALOGTEST_H
#define ADBLOCKBLOCKABLEITEMSDIALOGTEST_H

#include <QObject>

class AdBlockBlockableItemsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsDialogTest(QObject *parent = nullptr);
    ~AdBlockBlockableItemsDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // ADBLOCKBLOCKABLEITEMSDIALOGTEST_H
