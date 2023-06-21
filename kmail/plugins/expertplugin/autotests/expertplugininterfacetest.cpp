/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expertplugininterfacetest.h"

#include <QTest>

QTEST_MAIN(ExpertPluginInterfaceTest)

ExpertPluginInterfaceTest::ExpertPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

#include "moc_expertplugininterfacetest.cpp"
