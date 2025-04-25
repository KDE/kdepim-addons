/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskwidget.h"
#include "autogenerateconfigurelistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>

AutogenerateConfigureAskWidget::AutogenerateConfigureAskWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mTextEdit(new QPlainTextEdit(this))
    , mAutogenerateConfigureListView(new AutogenerateConfigureListView(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto vbox = new QVBoxLayout;
    vbox->setObjectName(QStringLiteral("vbox"));
    vbox->setContentsMargins({});
    mainLayout->addLayout(vbox);

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->addAction(QIcon::fromTheme(QStringLiteral("view-filter")), QLineEdit::LeadingPosition);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mAutogenerateConfigureListView, &AutogenerateConfigureListView::setFilterText);

    vbox->addWidget(mSearchLineEdit);

    mAutogenerateConfigureListView->setObjectName(QStringLiteral("mAutogenerateConfigureListView"));
    vbox->addWidget(mAutogenerateConfigureListView);

    mTextEdit->setObjectName(QStringLiteral("mTextEdit"));
    mainLayout->addWidget(mTextEdit);
}

AutogenerateConfigureAskWidget::~AutogenerateConfigureAskWidget() = default;

#include "moc_autogenerateconfigureaskwidget.cpp"
