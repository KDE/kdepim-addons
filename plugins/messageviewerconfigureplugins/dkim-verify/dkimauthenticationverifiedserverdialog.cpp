/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverdialog.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "DKIMAuthenticationVerifiedServerDialog";
}

DKIMAuthenticationVerifiedServerDialog::DKIMAuthenticationVerifiedServerDialog(QWidget *parent)
    : QDialog(parent)
    , mAuthenticationVerifiedWidget(new DKIMAuthenticationVerifiedServerWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Authentication Verified Server"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mAuthenticationVerifiedWidget->setObjectName(QStringLiteral("mAuthenticationVerifiedWidget"));
    mainLayout->addWidget(mAuthenticationVerifiedWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void DKIMAuthenticationVerifiedServerDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_dkimauthenticationverifiedserverdialog.cpp"
