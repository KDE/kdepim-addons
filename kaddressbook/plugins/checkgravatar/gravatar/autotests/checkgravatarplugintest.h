/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKGRAVATARPLUGINTEST_H
#define CHECKGRAVATARPLUGINTEST_H

#include <QObject>

class CheckGravatarPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckGravatarPluginTest(QObject *parent = nullptr);
    ~CheckGravatarPluginTest() = default;
};

#endif // CHECKGRAVATARPLUGINTEST_H
