/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef ADBLOCKRESULTTEST_H
#define ADBLOCKRESULTTEST_H

#include <QObject>

class AdBlockResultTest : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockResultTest(QObject *parent = nullptr);
    ~AdBlockResultTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeValid();
};

#endif // ADBLOCKRESULTTEST_H
