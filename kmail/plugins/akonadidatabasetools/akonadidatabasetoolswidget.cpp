/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolswidget.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>

AkonadiDatabaseToolsWidget::AkonadiDatabaseToolsWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mPlainTextEdit->setObjectName(QLatin1StringView("mPlainTextEdit"));
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);
}

AkonadiDatabaseToolsWidget::~AkonadiDatabaseToolsWidget() = default;

void AkonadiDatabaseToolsWidget::appendText(const QString &text)
{
    mPlainTextEdit->appendHtml(text);
}

#include "moc_akonadidatabasetoolswidget.cpp"
