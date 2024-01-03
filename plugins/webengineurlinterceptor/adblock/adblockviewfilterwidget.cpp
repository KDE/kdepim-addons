/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterwidget.h"
#include <QVBoxLayout>

AdblockViewFilterWidget::AdblockViewFilterWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    // TODO
}

AdblockViewFilterWidget::~AdblockViewFilterWidget() = default;

#include "moc_adblockviewfilterwidget.cpp"
