/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "checkbeforesendconfigurewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QCheckBox>
#include <KConfigGroup>
#include <KSharedConfig>

CheckBeforeSendConfigureWidget::CheckBeforeSendConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mCheckPlainTextMail = new QCheckBox(i18n("Send as plain text"), this);
    mCheckPlainTextMail->setObjectName(QStringLiteral("checkplaintext"));
    connect(mCheckPlainTextMail, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckPlainTextMail);

    mCheckMailTransport = new QCheckBox(i18n("Use SMTP server defined in identity"), this);
    mCheckMailTransport->setObjectName(QStringLiteral("smtpdefinedinidentity"));
    connect(mCheckMailTransport, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckMailTransport);

    mCheckDuplicateEmailsAddresses = new QCheckBox(i18n("Check duplicated emails addresses"), this);
    mCheckDuplicateEmailsAddresses->setObjectName(QStringLiteral("checkduplicatedemailsaddresses"));
    connect(mCheckDuplicateEmailsAddresses, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckDuplicateEmailsAddresses);

    mCheckSendAttachments = new QCheckBox(i18n("Check send attachment"), this);
    mCheckSendAttachments->setObjectName(QStringLiteral("checksendattachment"));
    connect(mCheckSendAttachments, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckSendAttachments);

    mainLayout->addStretch(1);
}

CheckBeforeSendConfigureWidget::~CheckBeforeSendConfigureWidget()
{
}

void CheckBeforeSendConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Check Before Send");
    mCheckPlainTextMail->setChecked(grp.readEntry("SendPlainText", false));
    mCheckMailTransport->setChecked(grp.readEntry("SmtpDefinedInIdentity", false));
    mCheckDuplicateEmailsAddresses->setChecked(grp.readEntry("CheckDuplicatedEmails", false));
    mCheckSendAttachments->setChecked(grp.readEntry("CheckSendAttachment", false));
}

void CheckBeforeSendConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Check Before Send");
    grp.writeEntry("SendPlainText", mCheckPlainTextMail->isChecked());
    grp.writeEntry("SmtpDefinedInIdentity", mCheckMailTransport->isChecked());
    grp.writeEntry("CheckDuplicatedEmails", mCheckDuplicateEmailsAddresses->isChecked());
    grp.writeEntry("CheckSendAttachment", mCheckSendAttachments->isChecked());
}

void CheckBeforeSendConfigureWidget::resetSettings()
{
    mCheckPlainTextMail->setChecked(false);
    mCheckMailTransport->setChecked(false);
    mCheckSendAttachments->setChecked(false);
    mCheckDuplicateEmailsAddresses->setChecked(false);
}
