/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTMAILDIALOGTEST_H
#define SELECTMAILDIALOGTEST_H

#include <QObject>

class SelectMailDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectMailDialogTest(QObject *parent = nullptr);
    ~SelectMailDialogTest() override = default;
};

#endif // SELECTMAILDIALOGTEST_H
