/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "confirmaddresswidget.h"

#include <KLocalizedString>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

ConfirmAddressWidget::ConfirmAddressWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    QLabel *lab = new QLabel(i18n("Potentially invalid emails are displayed in red:"), this);
    lab->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(lab);

    mListEmails = new QListWidget(this);
    mListEmails->setObjectName(QStringLiteral("listemails"));
    mainLayout->addWidget(mListEmails);
}

ConfirmAddressWidget::~ConfirmAddressWidget()
{

}

void ConfirmAddressWidget::setValidAddresses(const QStringList &addresses)
{
    createAddressItems(addresses, true);
}

void ConfirmAddressWidget::setInvalidAddresses(const QStringList &addresses)
{
    createAddressItems(addresses, false);
}

void ConfirmAddressWidget::createAddressItems(const QStringList &address, bool valid)
{
    Q_FOREACH (const QString &email, address) {
        QListWidgetItem *item = new QListWidgetItem(email, mListEmails);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if (!valid) {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setTextColor(Qt::red);
        } else {
            item->setFlags(item->flags() & ~ Qt::ItemIsUserCheckable);
        }
        mListEmails->addItem(item);
    }
}

QStringList ConfirmAddressWidget::whiteListSelectedEmails() const
{
    QStringList lst;
    const int nbItems(mListEmails->count());
    for (int i = 0; i < nbItems; ++i) {
        QListWidgetItem *item = mListEmails->item(i);
        if (item->checkState() == Qt::Checked) {
            lst << item->text();
        }
    }
    return lst;
}
