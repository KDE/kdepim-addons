/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessagebox.h"

#include <QVBoxLayout>

ConfirmBeforeDeletingMessageBox::ConfirmBeforeDeletingMessageBox(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
}

ConfirmBeforeDeletingMessageBox::~ConfirmBeforeDeletingMessageBox()
{
}
