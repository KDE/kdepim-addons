/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolswidget.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

AkonadiDatabaseToolsWidget::AkonadiDatabaseToolsWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins(QMargins{});
    mPlainTextEdit->setObjectName("mPlainTextEdit"_L1);
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);
}

AkonadiDatabaseToolsWidget::~AkonadiDatabaseToolsWidget() = default;

void AkonadiDatabaseToolsWidget::appendText(const QString &text)
{
    mPlainTextEdit->appendHtml(text.toHtmlEscaped());
}

#include "moc_akonadidatabasetoolswidget.cpp"
