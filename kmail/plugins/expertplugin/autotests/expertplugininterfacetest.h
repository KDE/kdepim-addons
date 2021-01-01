/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPERTPLUGININTERFACETEST_H
#define EXPERTPLUGININTERFACETEST_H

#include <QObject>

class ExpertPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ExpertPluginInterfaceTest(QObject *parent = nullptr);
    ~ExpertPluginInterfaceTest() = default;
};

#endif // EXPERTPLUGININTERFACETEST_H
