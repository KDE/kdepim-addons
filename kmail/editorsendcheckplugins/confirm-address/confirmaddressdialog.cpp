/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressdialog.h"
#include "confirmaddresswidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myConfigConfirmAddressDialog[] = "ConfirmAddressDialog";
}
ConfirmAddressDialog::ConfirmAddressDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmWidget(new ConfirmAddressWidget(this))
    , mWhiteListEmailsButton(new QPushButton(i18n("Add Selected Emails to WhiteList"), this))
{
    setWindowTitle(i18nc("@title:window", "Confirm Addresses"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfirmWidget->setObjectName(QStringLiteral("confirmwidget"));
    mainLayout->addWidget(mConfirmWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmAddressDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmAddressDialog::reject);

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
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigConfirmAddressDialog);
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void ConfirmAddressDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigConfirmAddressDialog);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
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

#include "moc_confirmaddressdialog.cpp"
