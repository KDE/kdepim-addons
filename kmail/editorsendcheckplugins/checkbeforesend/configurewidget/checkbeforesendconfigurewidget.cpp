/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

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
    , mCheckPlainTextMail(new QCheckBox(i18nc("@option:check", "Send as plain text"), this))
    , mCheckMailTransport(new QCheckBox(i18nc("@option:check", "Use SMTP server defined in identity"), this))
    , mCheckDuplicateEmailsAddresses(new QCheckBox(i18nc("@option:check", "Check duplicated emails addresses"), this))
    , mCheckSendAttachments(new QCheckBox(i18nc("@option:check", "Check send attachment"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mCheckPlainTextMail->setObjectName(QLatin1StringView("checkplaintext"));
    connect(mCheckPlainTextMail, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckPlainTextMail);

    mCheckMailTransport->setObjectName(QLatin1StringView("smtpdefinedinidentity"));
    connect(mCheckMailTransport, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckMailTransport);

    mCheckDuplicateEmailsAddresses->setObjectName(QLatin1StringView("checkduplicatedemailsaddresses"));
    connect(mCheckDuplicateEmailsAddresses, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckDuplicateEmailsAddresses);

    mCheckSendAttachments->setObjectName(QLatin1StringView("checksendattachment"));
    connect(mCheckSendAttachments, &QCheckBox::clicked, this, &CheckBeforeSendConfigureWidget::configureChanged);
    mainLayout->addWidget(mCheckSendAttachments);

    mainLayout->addStretch(1);
}

CheckBeforeSendConfigureWidget::~CheckBeforeSendConfigureWidget() = default;

void CheckBeforeSendConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    mCheckPlainTextMail->setChecked(grp.readEntry("SendPlainText", false));
    mCheckMailTransport->setChecked(grp.readEntry("SmtpDefinedInIdentity", false));
    mCheckDuplicateEmailsAddresses->setChecked(grp.readEntry("CheckDuplicatedEmails", false));
    mCheckSendAttachments->setChecked(grp.readEntry("CheckSendAttachment", false));
}

void CheckBeforeSendConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
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

#include "moc_checkbeforesendconfigurewidget.cpp"
