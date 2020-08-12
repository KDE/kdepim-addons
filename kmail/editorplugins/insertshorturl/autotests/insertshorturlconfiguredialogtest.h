/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INSERTSHORTURLCONFIGUREDIALOGTEST_H
#define INSERTSHORTURLCONFIGUREDIALOGTEST_H

#include <QObject>

class InsertShorturlConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureDialogTest(QObject *parent = nullptr);
    ~InsertShorturlConfigureDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // INSERTSHORTURLCONFIGUREDIALOGTEST_H
