/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigurelistviewtest.h"
#include "autogenerateconfigurelistview.h"
#include <QTest>
QTEST_MAIN(AutogenerateConfigureListViewTest)
AutogenerateConfigureListViewTest::AutogenerateConfigureListViewTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureListViewTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureListView w;
}

#include "moc_autogenerateconfigurelistviewtest.cpp"
