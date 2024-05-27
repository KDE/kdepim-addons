/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresswidget.h"

#include <KLocalizedString>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

ConfirmAddressWidget::ConfirmAddressWidget(QWidget *parent)
    : QWidget(parent)
    , mListEmails(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    auto lab = new QLabel(i18nc("@label:textbox", "Potentially invalid emails are displayed in red:"), this);
    lab->setObjectName(QLatin1StringView("label"));
    mainLayout->addWidget(lab);

    mListEmails->setObjectName(QLatin1StringView("listemails"));
    connect(mListEmails, &QListWidget::itemChanged, this, &ConfirmAddressWidget::slotItemChanged);
    mainLayout->addWidget(mListEmails);
}

ConfirmAddressWidget::~ConfirmAddressWidget() = default;

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

#include "moc_confirmaddresswidget.cpp"
