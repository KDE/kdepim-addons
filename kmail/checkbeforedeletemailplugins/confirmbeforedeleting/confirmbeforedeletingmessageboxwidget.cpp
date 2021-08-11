/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxwidget.h"
#include <QVBoxLayout>

ConfirmBeforeDeletingMessageBoxWidget::ConfirmBeforeDeletingMessageBoxWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
}

ConfirmBeforeDeletingMessageBoxWidget::~ConfirmBeforeDeletingMessageBoxWidget()
{
}
