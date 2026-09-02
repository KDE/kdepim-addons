/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidget.h"
#include "dkimauthenticationverifiedserverdialog.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
using namespace Qt::Literals::StringLiterals;

DKIMAdvancedWidget::DKIMAdvancedWidget(QWidget *parent)
    : QWidget(parent)
    , mSha1Policy(new QComboBox(this))
    , mCheckDKIMWhenOnlyTesting(new QCheckBox(i18nc("@option:check", "Still verify the signature, if a domain is only testing DKIM"), this))
    , mUseAuthenticationResultRelaxedParser(new QCheckBox(i18nc("@option:check", "Use relaxed parsing when reading \"Authentication-Result\" header"), this))
    , mSmallKeyPolicy(new QComboBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mCheckDKIMWhenOnlyTesting->setObjectName("kcfg_VerifySignatureWhenOnlyTest"_L1);
    mainLayout->addRow(mCheckDKIMWhenOnlyTesting);

    mUseAuthenticationResultRelaxedParser->setObjectName("kcfg_UseRelaxedParsingAuthenticationResults"_L1);
    mainLayout->addRow(mUseAuthenticationResultRelaxedParser);

    mSha1Policy->setObjectName("kcfg_PolicyRsaSha1"_L1);
    mSha1Policy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat RSA-SHA1 sign algorithm as:"), mSha1Policy);

    mSmallKeyPolicy->setObjectName("kcfg_PublicRsaTooSmall"_L1);
    mSmallKeyPolicy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat small Key as:"), mSmallKeyPolicy);

    auto configureServer = new QPushButton(i18nc("@action:button", "Configure"), this);
    configureServer->setObjectName("configure_button"_L1);
    connect(configureServer, &QPushButton::clicked, this, &DKIMAdvancedWidget::slotConfigureAuthenticationServer);
    mainLayout->addRow(i18n("Authentication Server verified:"), configureServer);
}

DKIMAdvancedWidget::~DKIMAdvancedWidget() = default;

void DKIMAdvancedWidget::slotConfigureAuthenticationServer()
{
    DKIMAuthenticationVerifiedServerDialog dlg(this);
    dlg.exec();
}

#include "moc_dkimadvancedwidget.cpp"
