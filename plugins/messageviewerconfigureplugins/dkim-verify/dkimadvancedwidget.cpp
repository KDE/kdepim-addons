/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidget.h"
#include "dkimauthenticationverifiedserverdialog.h"
#include <KLocalizedString>
#include <MessageViewer/MessageViewerSettings>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>

DKIMAdvancedWidget::DKIMAdvancedWidget(QWidget *parent)
    : QWidget(parent)
    , mSha1Policy(new QComboBox(this))
    , mCheckDKIMWhenOnlyTesting(new QCheckBox(i18n("Still verify the signature, if a domain is only testing DKIM"), this))
    , mUseAuthenticationResultRelaxedParser(new QCheckBox(i18n("Use relaxed parsing when reading \"Authentication-Result\" header"), this))
    , mSmallKeyPolicy(new QComboBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mCheckDKIMWhenOnlyTesting->setObjectName(QLatin1StringView("kcfg_VerifySignatureWhenOnlyTest"));
    mainLayout->addRow(mCheckDKIMWhenOnlyTesting);

    mUseAuthenticationResultRelaxedParser->setObjectName(QLatin1StringView("kcfg_UseRelaxedParsingAuthenticationResults"));
    mainLayout->addRow(mUseAuthenticationResultRelaxedParser);

    mSha1Policy->setObjectName(QLatin1StringView("kcfg_PolicyRsaSha1"));
    mSha1Policy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat RSA-SHA1 sign algorithm as:"), mSha1Policy);

    mSmallKeyPolicy->setObjectName(QLatin1StringView("kcfg_PublicRsaTooSmall"));
    mSmallKeyPolicy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat small Key as:"), mSmallKeyPolicy);

    auto configureServer = new QPushButton(i18n("Configure"), this);
    configureServer->setObjectName(QLatin1StringView("configure_button"));
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
