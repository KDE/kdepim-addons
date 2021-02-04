/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresswidget.h"

#include <KLocalizedString>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

ConfirmAddressWidget::ConfirmAddressWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    QLabel *lab = new QLabel(i18n("Potentially invalid emails are displayed in red:"), this);
    lab->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(lab);

    mListEmails = new QListWidget(this);
    mListEmails->setObjectName(QStringLiteral("listemails"));
    connect(mListEmails, &QListWidget::itemChanged, this, &ConfirmAddressWidget::slotItemChanged);
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
    for (const QString &email : address) {
        auto item = new QListWidgetItem(email, mListEmails);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if (valid) {
            item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        } else {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setForeground(Qt::red);
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

void ConfirmAddressWidget::slotItemChanged(QListWidgetItem *)
{
    bool hasElementChecked = false;
    const int nbItems(mListEmails->count());
    for (int i = 0; i < nbItems; ++i) {
        QListWidgetItem *item = mListEmails->item(i);
        if (item->checkState() == Qt::Checked) {
            hasElementChecked = true;
            break;
        }
    }
    Q_EMIT updateButtonStatus(hasElementChecked);
}
