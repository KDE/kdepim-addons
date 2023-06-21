/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendinterface.h"
#include "checkbeforesendupdatesmtpdialog.h"
#include "duplicateemails/checkduplicateemailsdialog.h"
#include "duplicateemails/checkduplicateemailsjob.h"
#include "sendattachments/checkattachmentdialog.h"
#include "sendattachments/checkattachmentjob.h"

#include <KConfigGroup>
#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>

#include <QPointer>

CheckBeforeSendInterface::CheckBeforeSendInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent)
{
}

CheckBeforeSendInterface::~CheckBeforeSendInterface() = default;

bool CheckBeforeSendInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    if (mSendPlainText) {
        if (params.isHtmlMail()) {
            const int answer = KMessageBox::questionTwoActions(parentWidget(),
                                                               i18n("Do you want to send the email as HTML?"),
                                                               i18n("Send email as plain text"),
                                                               KGuiItem(i18nc("@action:button", "Send As HTML")),
                                                               KStandardGuiItem::cancel());
            if (answer == KMessageBox::ButtonCode::SecondaryAction) {
                return false;
            }
        }
    }
    if (mCheckMailTransport) {
        KIdentityManagementCore::Identity *identity = &KIdentityManagementCore::IdentityManager::self()->modifyIdentityForUoid(params.identity());
        if (identity->transport() != QString::number(params.transportId())) {
            QPointer<CheckBeforeSendUpdateSmtpDialog> dlg = new CheckBeforeSendUpdateSmtpDialog(parentWidget());
            if (!dlg->exec()) {
                delete dlg;
                return false;
            }
            if (dlg->changeSmtp()) {
                identity->setTransport(QString::number(params.transportId()));
                KIdentityManagementCore::IdentityManager::self()->commit();
            }
            delete dlg;
        }
    }
    if (mCheckDuplicateEmails) {
        QStringList lst;
        if (!params.ccAddresses().trimmed().isEmpty()) {
            lst << params.ccAddresses();
        }
        if (!params.bccAddresses().trimmed().isEmpty()) {
            lst << params.bccAddresses();
        }
        if (!params.toAddresses().trimmed().isEmpty()) {
            lst << params.toAddresses();
        }
        if (!lst.isEmpty()) {
            CheckDuplicateEmailsJob job;
            job.setEmails(lst);
            job.start();
            const QMap<QString, int> results = job.result();
            if (!results.isEmpty()) {
                QPointer<CheckDuplicateEmailsDialog> dlg = new CheckDuplicateEmailsDialog(parentWidget());
                dlg->setDuplicatedEmails(results);
                bool result = false;
                if (dlg->exec()) {
                    result = true;
                } else {
                    result = false;
                }
                delete dlg;
                if (!result) {
                    return result;
                }
            }
        }
    }
    if (mCheckSendAttachments) {
        if (params.hasAttachment()) {
            QPointer<CheckAttachmentDialog> dlg = new CheckAttachmentDialog(parentWidget());
            QStringList lst;
            if (!params.ccAddresses().trimmed().isEmpty()) {
                lst << params.ccAddresses();
            }
            if (!params.bccAddresses().trimmed().isEmpty()) {
                lst << params.bccAddresses();
            }
            if (!params.toAddresses().trimmed().isEmpty()) {
                lst << params.toAddresses();
            }
            CheckAttachmentJob job;
            job.setOriginalEmails(lst);
            job.start();
            dlg->setEmails(job.resultList());
            if (dlg->exec()) {
                delete dlg;
                return true;
            } else {
                delete dlg;
                return false;
            }
        }
    }
    return true;
}

void CheckBeforeSendInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Check Before Send");
    mSendPlainText = grp.readEntry("SendPlainText", false);
    mCheckMailTransport = grp.readEntry("SmtpDefinedInIdentity", false);
    mCheckDuplicateEmails = grp.readEntry("CheckDuplicatedEmails", false);
    mCheckSendAttachments = grp.readEntry("CheckSendAttachment", false);
}

#include "moc_checkbeforesendinterface.cpp"
