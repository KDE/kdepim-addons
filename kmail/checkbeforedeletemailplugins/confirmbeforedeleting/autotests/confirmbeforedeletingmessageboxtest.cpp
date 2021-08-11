/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxtest.h"
#include "confirmbeforedeletingmessagebox.h"
#include <QTest>
QTEST_MAIN(ConfirmBeforeDeletingMessageBoxTest)
ConfirmBeforeDeletingMessageBoxTest::ConfirmBeforeDeletingMessageBoxTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingMessageBoxTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingMessageBox d;
    // TODO
}
