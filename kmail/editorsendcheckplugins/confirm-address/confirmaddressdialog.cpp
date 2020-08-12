/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressdialog.h"
#include "confirmaddresswidget.h"
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <KMessageBox>

ConfirmAddressDialog::ConfirmAddressDialog(QWidget *parent)
    : QDialog(parent)
    , mCurrentIdentity(0)
{
    setWindowTitle(i18nc("@title:window", "Confirm Addresses"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfirmWidget = new ConfirmAddressWidget(this);
    mConfirmWidget->setObjectName(QStringLiteral("confirmwidget"));
    mainLayout->addWidget(mConfirmWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmAddressDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmAddressDialog::reject);

    mWhiteListEmailsButton = new QPushButton(i18n("Add Selected Emails to WhiteList"));
    mWhiteListEmailsButton->setObjectName(QStringLiteral("whiteListEmailsButton"));
    mWhiteListEmailsButton->setEnabled(false);
    buttonBox->addButton(mWhiteListEmailsButton, QDialogButtonBox::ActionRole);
    connect(mWhiteListEmailsButton, &QPushButton::clicked, this, &ConfirmAddressDialog::slotWhiteListSelectedEmails);
    connect(mConfirmWidget, &ConfirmAddressWidget::updateButtonStatus, mWhiteListEmailsButton, &QPushButton::setEnabled);

    mainLayout->addWidget(buttonBox);
    readConfig();
}

ConfirmAddressDialog::~ConfirmAddressDialog()
{
    writeConfig();
}

void ConfirmAddressDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfirmAddressDialog");
    group.writeEntry("Size", size());
}

void ConfirmAddressDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfirmAddressDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ConfirmAddressDialog::setValidAddresses(const QStringList &addresses)
{
    mConfirmWidget->setValidAddresses(addresses);
}

void ConfirmAddressDialog::setInvalidAddresses(const QStringList &addresses)
{
    mConfirmWidget->setInvalidAddresses(addresses);
}

void ConfirmAddressDialog::setCurrentIdentity(uint identity)
{
    mCurrentIdentity = identity;
}

void ConfirmAddressDialog::slotWhiteListSelectedEmails()
{
    const QStringList whiteListEmails = mConfirmWidget->whiteListSelectedEmails();
    if (!whiteListEmails.isEmpty()) {
        Q_EMIT addWhileListEmails(whiteListEmails, mCurrentIdentity);
        KMessageBox::information(this, i18n("All selected emails are added to white list"), i18n("Emails added to white list"));
    }
}
