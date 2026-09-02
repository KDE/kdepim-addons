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
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    auto checkDKIMWhenOnlyTesting = new QCheckBox(i18nc("@option:check", "Still verify the signature, if a domain is only testing DKIM"), this);
    checkDKIMWhenOnlyTesting->setObjectName("kcfg_VerifySignatureWhenOnlyTest"_L1);
    mainLayout->addRow(checkDKIMWhenOnlyTesting);

    auto useAuthenticationResultRelaxedParser =
        new QCheckBox(i18nc("@option:check", "Use relaxed parsing when reading \"Authentication-Result\" header"), this);
    useAuthenticationResultRelaxedParser->setObjectName("kcfg_UseRelaxedParsingAuthenticationResults"_L1);
    mainLayout->addRow(useAuthenticationResultRelaxedParser);

    auto sha1Policy = new QComboBox(this);
    sha1Policy->setObjectName("kcfg_PolicyRsaSha1"_L1);
    sha1Policy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat RSA-SHA1 sign algorithm as:"), sha1Policy);

    auto smallKeyPolicy = new QComboBox(this);
    smallKeyPolicy->setObjectName("kcfg_PublicRsaTooSmall"_L1);
    smallKeyPolicy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat small Key as:"), smallKeyPolicy);

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
