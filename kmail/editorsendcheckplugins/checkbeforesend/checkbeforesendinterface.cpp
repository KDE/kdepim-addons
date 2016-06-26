/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "checkbeforesendinterface.h"
#include "checkduplicateemailsjob.h"
#include "checkduplicateemailsdialog.h"

#include <KMessageBox>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>
#include <KIdentityManagement/Identity>
#include <KIdentityManagement/IdentityManager>

#include <QPointer>

CheckBeforeSendInterface::CheckBeforeSendInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent),
      mIdentityManager(Q_NULLPTR),
      mSendPlainText(false),
      mCheckMailTransport(false),
      mCheckDuplicateEmails(false)
{
    reloadConfig();
}

CheckBeforeSendInterface::~CheckBeforeSendInterface()
{

}

bool CheckBeforeSendInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    if (mSendPlainText) {
        if (params.isHtmlMail()) {
            if (KMessageBox::No == KMessageBox::questionYesNo(parentWidget(), i18n("Do you want to send the email as HTML?"), i18n("Send email as plain text"))) {
                return false;
            } else {
                return true;
            }
        }
    }
    if (mCheckMailTransport) {
        if (!mIdentityManager) {
            mIdentityManager = new KIdentityManagement::IdentityManager(true, this);
        }
        const KIdentityManagement::Identity identity = mIdentityManager->identityForUoid(params.identity());
        if (identity.transport() != QString::number(params.transportId())) {
            if (KMessageBox::No == KMessageBox::questionYesNo(parentWidget(), i18n("Do you want to send the email with a different SMTP than the one defined in the current identity?"), i18n("Check SMTP server"))) {
                return false;
            } else {
                return true;
            }
        }
    }
    if (mCheckDuplicateEmails) {
        const QStringList lst{ params.bccAddresses(), params.toAddresses(), params.ccAddresses() };

        if (!lst.isEmpty()) {
            CheckDuplicateEmailsJob job;
            job.setEmails(lst);
            job.start();
            const QMap<QString, int> results = job.result();
            if (!results.isEmpty()) {
                QPointer<CheckDuplicateEmailsDialog> dlg = new CheckDuplicateEmailsDialog(parentWidget());
                dlg->setDuplicatedEmails(results);
                if (dlg->exec()) {
                    delete dlg;
                    return true;
                } else {
                    delete dlg;
                    return false;
                }
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
}
