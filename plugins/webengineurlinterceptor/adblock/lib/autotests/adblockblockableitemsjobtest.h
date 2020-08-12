/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKBLOCKABLEITEMSJOBTEST_H
#define ADBLOCKBLOCKABLEITEMSJOBTEST_H

#include <QObject>

class AdBlockBlockableItemsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsJobTest(QObject *parent = nullptr);
    ~AdBlockBlockableItemsJobTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReturnEmptyListWhenWebEngineIsNotSet();
    void shouldReturnAddBlockItem();
};

#endif // ADBLOCKBLOCKABLEITEMSJOBTEST_H
