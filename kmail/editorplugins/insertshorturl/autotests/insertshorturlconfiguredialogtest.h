/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

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
    ~InsertShorturlConfigureDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // INSERTSHORTURLCONFIGUREDIALOGTEST_H
