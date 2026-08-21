/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdowninterfacetest.h"
#include "../plugin/markdowninterface.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(MarkdownInterfaceTest)

MarkdownInterfaceTest::MarkdownInterfaceTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void MarkdownInterfaceTest::shouldHaveDefaultValue()
{
}

#include "moc_markdowninterfacetest.cpp"
