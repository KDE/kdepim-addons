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

#include <KMessageBox>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>
#include <KIdentityManagement/Identity>
#include <KIdentityManagement/IdentityManager>

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
            if (KMessageBox::No == KMessageBox::questionYesNo(parentWidget(), i18n("Do you want to send mail as HTML?"), i18n("Send Mail as PlainText"))) {
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
            if (KMessageBox::No == KMessageBox::questionYesNo(parentWidget(), i18n("Do you want to send mail with a different SMTP that defined in current identity?"), i18n("Check SMTP server"))) {
                return false;
            } else {
                return true;
            }
        }
    }
    if (mCheckDuplicateEmails) {
        //TODO
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
