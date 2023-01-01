/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdowninterfacetest.h"
#include "../plugin/markdowninterface.h"
#include <QTest>
QTEST_MAIN(MarkdownInterfaceTest)

MarkdownInterfaceTest::MarkdownInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownInterfaceTest::shouldHaveDefaultValue()
{
}
