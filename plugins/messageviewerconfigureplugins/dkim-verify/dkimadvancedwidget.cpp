/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QPointer>
#include <QPushButton>
#include "dkimauthenticationverifiedserverdialog.h"
#include <MessageViewer/MessageViewerSettings>
#include <PimCommon/ConfigureImmutableWidgetUtils>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
using namespace PimCommon::ConfigureImmutableWidgetUtils;

DKIMAdvancedWidget::DKIMAdvancedWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mCheckDKIMWhenOnlyTesting = new QCheckBox(i18n("Still verify the signature, if a domain is only testing DKIM"), this);
    mCheckDKIMWhenOnlyTesting->setObjectName(QStringLiteral("mCheckDKIMWhenOnlyTesting"));
    mainLayout->addRow(mCheckDKIMWhenOnlyTesting);

    mUseAuthenticationResultRelaxedParser = new QCheckBox(i18n("Use relaxed parsing when reading \"Authentication-Result\" header"), this);
    mUseAuthenticationResultRelaxedParser->setObjectName(QStringLiteral("mUseAuthenticationResultRelaxedParser"));
    mainLayout->addRow(mUseAuthenticationResultRelaxedParser);

    mSha1Policy = new QComboBox(this);
    mSha1Policy->setObjectName(QStringLiteral("rsa1-policy"));
    mSha1Policy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat RSA-SHA1 sign algorithm as:"), mSha1Policy);

    mSmallKeyPolicy = new QComboBox(this);
    mSmallKeyPolicy->setObjectName(QStringLiteral("mSmallKeyPolicy"));
    mSmallKeyPolicy->addItems({i18n("Nothing"), i18n("Warning"), i18n("Error")});
    mainLayout->addRow(i18n("Treat small Key as:"), mSmallKeyPolicy);

    QPushButton *configureServer = new QPushButton(i18n("Configure"), this);
    configureServer->setObjectName(QStringLiteral("configure_button"));
    connect(configureServer, &QPushButton::clicked, this, &DKIMAdvancedWidget::slotConfigureAuthenticationServer);
    mainLayout->addRow(i18n("Authentication Server verified:"), configureServer);
}

DKIMAdvancedWidget::~DKIMAdvancedWidget()
{
}

void DKIMAdvancedWidget::slotConfigureAuthenticationServer()
{
    QPointer<DKIMAuthenticationVerifiedServerDialog> dlg = new DKIMAuthenticationVerifiedServerDialog(this);
    dlg->exec();
    delete dlg;
}

void DKIMAdvancedWidget::loadSettings()
{
    loadWidget(mSha1Policy, MessageViewer::MessageViewerSettings::self()->policyRsaSha1Item());
    loadWidget(mCheckDKIMWhenOnlyTesting, MessageViewer::MessageViewerSettings::self()->verifySignatureWhenOnlyTestItem());
    loadWidget(mUseAuthenticationResultRelaxedParser, MessageViewer::MessageViewerSettings::self()->useRelaxedParsingAuthenticationResultsItem());
    loadWidget(mSmallKeyPolicy, MessageViewer::MessageViewerSettings::self()->publicRsaTooSmallItem());
}

void DKIMAdvancedWidget::saveSettings()
{
    saveComboBox(mSha1Policy, MessageViewer::MessageViewerSettings::self()->policyRsaSha1Item());
    saveCheckBox(mCheckDKIMWhenOnlyTesting, MessageViewer::MessageViewerSettings::self()->verifySignatureWhenOnlyTestItem());
    saveCheckBox(mUseAuthenticationResultRelaxedParser, MessageViewer::MessageViewerSettings::self()->useRelaxedParsingAuthenticationResultsItem());
    saveComboBox(mSmallKeyPolicy, MessageViewer::MessageViewerSettings::self()->publicRsaTooSmallItem());
}

void DKIMAdvancedWidget::resetSettings()
{
    const bool bUseDefaults = MessageViewer::MessageViewerSettings::self()->useDefaults(true);
    loadSettings();
    MessageViewer::MessageViewerSettings::self()->useDefaults(bUseDefaults);
}
