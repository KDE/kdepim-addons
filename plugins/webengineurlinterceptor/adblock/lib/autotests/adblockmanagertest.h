/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKMANAGERTEST_H
#define ADBLOCKMANAGERTEST_H

#include <QObject>

class AdblockManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockManagerTest(QObject *parent = nullptr);
    ~AdblockManagerTest();
};

#endif // ADBLOCKMANAGERTEST_H
