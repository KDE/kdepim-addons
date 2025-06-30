/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmaildialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include <QTest>
QTEST_MAIN(SelectMailDialogTest)

SelectMailDialogTest::SelectMailDialogTest(QObject *parent)
    : QObject(parent)
{
}

#include "moc_selectmaildialogtest.cpp"
