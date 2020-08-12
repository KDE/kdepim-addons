/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARUPDATEDIALOGTEST_H
#define GRAVATARUPDATEDIALOGTEST_H

#include <QObject>

class GravatarUpdateDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateDialogTest(QObject *parent = nullptr);
    ~GravatarUpdateDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAVATARUPDATEDIALOGTEST_H
