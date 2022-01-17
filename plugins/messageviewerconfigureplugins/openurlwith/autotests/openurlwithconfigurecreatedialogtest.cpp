/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatedialogtest.h"
#include "openurlwithconfigurecreatedialog.h"
#include <QTest>
QTEST_MAIN(OpenUrlWithConfigureCreateDialogTest)
OpenUrlWithConfigureCreateDialogTest::OpenUrlWithConfigureCreateDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateDialogTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateDialog d;
    // TODO
}
