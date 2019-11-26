/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimadvancedwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include "messageviewer/messageviewersettings.h"
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
    mainLayout->setContentsMargins(0, 0, 0, 0);

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
}

DKIMAdvancedWidget::~DKIMAdvancedWidget()
{
}

void DKIMAdvancedWidget::loadSettings()
{
    loadWidget(mSha1Policy, MessageViewer::MessageViewerSettings::self()->policyRsaSha1Item());
    loadWidget(mCheckDKIMWhenOnlyTesting, MessageViewer::MessageViewerSettings::self()->verifySignatureWhenOnlyTestItem());
    loadWidget(mUseAuthenticationResultRelaxedParser, MessageViewer::MessageViewerSettings::self()->useRelaxedParsingAuthenticationResultsItem());
}

void DKIMAdvancedWidget::saveSettings()
{
    saveComboBox(mSha1Policy, MessageViewer::MessageViewerSettings::self()->policyRsaSha1Item());
    saveCheckBox(mCheckDKIMWhenOnlyTesting, MessageViewer::MessageViewerSettings::self()->verifySignatureWhenOnlyTestItem());
    saveCheckBox(mUseAuthenticationResultRelaxedParser, MessageViewer::MessageViewerSettings::self()->useRelaxedParsingAuthenticationResultsItem());
}

void DKIMAdvancedWidget::resetSettings()
{
    const bool bUseDefaults = MessageViewer::MessageViewerSettings::self()->useDefaults(true);
    loadSettings();
    MessageViewer::MessageViewerSettings::self()->useDefaults(bUseDefaults);
}
