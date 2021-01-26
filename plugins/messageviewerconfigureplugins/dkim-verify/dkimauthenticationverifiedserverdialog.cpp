/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverdialog.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace
{
static const char myConfigGroupName[] = "DKIMAuthenticationVerifiedServerDialog";
}

DKIMAuthenticationVerifiedServerDialog::DKIMAuthenticationVerifiedServerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Authentication Verified Server"));
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mAuthenticationVerifiedWidget = new DKIMAuthenticationVerifiedServerWidget(this);
    mAuthenticationVerifiedWidget->setObjectName(QStringLiteral("mAuthenticationVerifiedWidget"));
    mainLayout->addWidget(mAuthenticationVerifiedWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMAuthenticationVerifiedServerDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMAuthenticationVerifiedServerDialog::reject);
    mAuthenticationVerifiedWidget->loadSettings();
    readConfig();
}

DKIMAuthenticationVerifiedServerDialog::~DKIMAuthenticationVerifiedServerDialog()
{
    writeConfig();
}

void DKIMAuthenticationVerifiedServerDialog::slotAccepted()
{
    mAuthenticationVerifiedWidget->saveSettings();
    accept();
}

void DKIMAuthenticationVerifiedServerDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void DKIMAuthenticationVerifiedServerDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
    group.sync();
}
