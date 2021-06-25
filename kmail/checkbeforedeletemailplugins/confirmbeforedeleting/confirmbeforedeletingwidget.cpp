/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidget.h"
#include <QVBoxLayout>

ConfirmBeforeDeletingWidget::ConfirmBeforeDeletingWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    // TODO
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget()
{
}
