/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectmailwidget.h"

#include <QHBoxLayout>
#include <QTreeView>

#include <Akonadi/Contact/EmailAddressSelectionWidget>

SelectMailWidget::SelectMailWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    //TODO customize it
    mView = new Akonadi::EmailAddressSelectionWidget(this);
    layout->addWidget(mView);
    mView->view()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mView->view()->setAlternatingRowColors(true);
    mView->view()->setSortingEnabled(true);
    mView->view()->sortByColumn(0, Qt::AscendingOrder);
}

SelectMailWidget::~SelectMailWidget()
{

}

QStringList SelectMailWidget::selectedEmails() const
{
    QStringList lst;
    for (const Akonadi::EmailAddressSelection &selection : mView->selectedAddresses()) {
        lst.append(selection.quotedEmail());
    }

    return lst;
}
