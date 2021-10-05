/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmailwidget.h"

#include <QHBoxLayout>
#include <QTreeView>

#include <Akonadi/Contact/EmailAddressSelectionWidget>

SelectMailWidget::SelectMailWidget(QWidget *parent)
    : QWidget(parent)
    , mView(new Akonadi::EmailAddressSelectionWidget(true, nullptr, this))
{
    auto layout = new QHBoxLayout(this);
    layout->setObjectName(QStringLiteral("mainlayout"));
    layout->setContentsMargins({});

    mView->setObjectName(QStringLiteral("emailaddressselectionwidget"));
    layout->addWidget(mView);
    mView->view()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mView->view()->setAlternatingRowColors(true);
    mView->view()->setSortingEnabled(true);
    mView->view()->sortByColumn(0, Qt::AscendingOrder);
    connect(mView, &Akonadi::EmailAddressSelectionWidget::doubleClicked, this, &SelectMailWidget::doubleClicked);
}

SelectMailWidget::~SelectMailWidget()
{
}

QStringList SelectMailWidget::selectedEmails() const
{
    QStringList lst;
    const auto selectedAddress = mView->selectedAddresses();
    lst.reserve(selectedAddress.count());
    for (const Akonadi::EmailAddressSelection &selection : selectedAddress) {
        lst.append(selection.email());
    }
    return lst;
}
