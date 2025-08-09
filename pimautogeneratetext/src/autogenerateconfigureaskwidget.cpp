/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskwidget.h"
#include "autogenerateconfigureaskmodel.h"
#include "autogenerateconfigurelistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QVBoxLayout>

AutogenerateConfigureAskWidget::AutogenerateConfigureAskWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mTextEdit(new QPlainTextEdit(this))
    , mSplitter(new QSplitter(this))
    , mAutogenerateConfigureListView(new AutogenerateConfigureListView(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSplitter->setObjectName(QStringLiteral("mSplitter"));

    auto widget = new QWidget(this);

    auto vbox = new QVBoxLayout(widget);
    vbox->setObjectName(QStringLiteral("vbox"));
    vbox->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->addAction(QIcon::fromTheme(QStringLiteral("view-filter")), QLineEdit::LeadingPosition);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mAutogenerateConfigureListView, &AutogenerateConfigureListView::setFilterText);

    vbox->addWidget(mSearchLineEdit);

    mAutogenerateConfigureListView->setObjectName(QStringLiteral("mAutogenerateConfigureListView"));
    vbox->addWidget(mAutogenerateConfigureListView);
    connect(mAutogenerateConfigureListView->selectionModel(), &QItemSelectionModel::currentChanged, this, &AutogenerateConfigureAskWidget::slotItemChanged);

    mSplitter->addWidget(widget);

    mSplitter->addWidget(mTextEdit);
    mTextEdit->setObjectName(QStringLiteral("mTextEdit"));
    mainLayout->addWidget(mSplitter);
}

AutogenerateConfigureAskWidget::~AutogenerateConfigureAskWidget() = default;

void AutogenerateConfigureAskWidget::slotItemChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current == previous) {
        return;
    }
    if (previous.isValid()) {
        mAutogenerateConfigureListView->setData(previous, mTextEdit->toPlainText());
    }
    if (current.isValid()) {
        mTextEdit->setPlainText(current.data(AutogenerateConfigureAskModel::TextRole).toString());
    } else {
        mTextEdit->setPlainText({});
    }
}

QList<AutogenerateConfigureAskInfo> AutogenerateConfigureAskWidget::askInfos() const
{
    return mAutogenerateConfigureListView->askInfos();
}

void AutogenerateConfigureAskWidget::setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems)
{
    mAutogenerateConfigureListView->setAskInfos(newAskItems);
}

#include "moc_autogenerateconfigureaskwidget.cpp"
