/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>
namespace
{
static const char myConfigGroupName[] = "Check Before Send";
}
CheckBeforeSendConfigureWidget::CheckBeforeSendConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mCheckPlainTextMail(new QCheckBox(i18n("Send as plain text"), this))
    , mCheckMailTransport(new QCheckBox(i18n("Use SMTP server defined in identity"), this))
    , mCheckDuplicateEmailsAddresses(new QCheckBox(i18n("Check duplicated emails addresses"), this))
    , mCheckSendAttachments(new QCheckBox(i18n("Check send attachment"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mCheckPlainTextMail->setObjectName(QStringLiteral("checkplaintext"));
    connect(mCheckPlainTextMail, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckPlainTextMail);

    mCheckMailTransport->setObjectName(QStringLiteral("smtpdefinedinidentity"));
    connect(mCheckMailTransport, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckMailTransport);

    mCheckDuplicateEmailsAddresses->setObjectName(QStringLiteral("checkduplicatedemailsaddresses"));
    connect(mCheckDuplicateEmailsAddresses, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckDuplicateEmailsAddresses);

    mCheckSendAttachments->setObjectName(QStringLiteral("checksendattachment"));
    connect(mCheckSendAttachments, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckSendAttachments);

    mainLayout->addStretch(1);
}

CheckBeforeSendConfigureWidget::~CheckBeforeSendConfigureWidget() = default;

void CheckBeforeSendConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    mCheckPlainTextMail->setChecked(grp.readEntry("SendPlainText", false));
    mCheckMailTransport->setChecked(grp.readEntry("SmtpDefinedInIdentity", false));
    mCheckDuplicateEmailsAddresses->setChecked(grp.readEntry("CheckDuplicatedEmails", false));
    mCheckSendAttachments->setChecked(grp.readEntry("CheckSendAttachment", false));
}

void CheckBeforeSendConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
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
