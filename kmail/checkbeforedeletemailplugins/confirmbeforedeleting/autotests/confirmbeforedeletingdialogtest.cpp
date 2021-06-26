/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingdialogtest.h"
#include "confirmbeforedeletingdialog.h"
#include <QTest>
QTEST_MAIN(ConfirmBeforeDeletingDialogTest)
ConfirmBeforeDeletingDialogTest::ConfirmBeforeDeletingDialogTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingDialogTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingDialog d;
    // TODO
}
