/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPCREATEFOLDERJOBTEST_H
#define SELECTIMAPCREATEFOLDERJOBTEST_H

#include <QObject>

class SelectImapCreateJobTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapCreateJobTest(QObject *parent = nullptr);
    ~SelectImapCreateJobTest();
};

#endif // SELECTIMAPCREATEJOBTEST_H
