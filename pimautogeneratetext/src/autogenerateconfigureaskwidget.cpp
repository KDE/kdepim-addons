/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskwidget.h"
#include "autogenerateconfigurelistview.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>

AutogenerateConfigureAskWidget::AutogenerateConfigureAskWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);

    mTextEdit->setObjectName(QStringLiteral("mTextEdit"));
    mainLayout->addWidget(mTextEdit);
}

AutogenerateConfigureAskWidget::~AutogenerateConfigureAskWidget() = default;

#include "moc_autogenerateconfigureaskwidget.cpp"
