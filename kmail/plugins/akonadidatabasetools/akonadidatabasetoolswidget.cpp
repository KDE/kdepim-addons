/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolswidget.h"
#include <QVBoxLayout>

AkonadiDatabaseToolsWidget::AkonadiDatabaseToolsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
}

AkonadiDatabaseToolsWidget::~AkonadiDatabaseToolsWidget() = default;

void AkonadiDatabaseToolsWidget::appendText(const QString &text)
{
    // TODO
}
