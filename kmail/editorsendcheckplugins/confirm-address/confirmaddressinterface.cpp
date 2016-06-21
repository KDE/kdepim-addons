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

#include "confirmaddressinterface.h"
#include "confirmaddressconfigurewidget.h"
#include "confirmaddressdialog.h"
#include "confirmaddresscheckjob.h"

#include <QPointer>
#include <KConfigGroup>
#include <KSharedConfig>

#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>
#include <MessageComposer/AliasesExpandJob>

ConfirmAddressInterface::ConfirmAddressInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent),
      mEnabled(false)
{
    reloadConfig();
}

ConfirmAddressInterface::~ConfirmAddressInterface()
{

}

bool ConfirmAddressInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    if (mEnabled) {
        const QStringList lst{ params.bccAddresses(), params.toAddresses(), params.ccAddresses() };
        if (lst.isEmpty()) {
            return true;
        }
        // not configurated => validate it.
        const ConfirmAddressSettings settings = mHashSettings.value(params.identity());
        if (settings.mDomains.isEmpty() && settings.mWhiteLists.isEmpty()) {
            return true;
        }
        const QString str = lst.join(QStringLiteral(", "));
        const QStringList emails = str.split(QStringLiteral(", "));
#if 0
        MessageComposer::AliasesExpandJob job(params.addresses().join(QStringLiteral(", ")), params.defaultDomain(), this);
        if (job.exec()) {
            emails = job.emailAddressOnly();
        }
#endif
        ConfirmAddressCheckJob job;
        job.setCheckSettings(settings.mDomains, settings.mWhiteLists);
        job.setAddressList(emails);
        job.start();

        const QStringList invalidEmails = job.invalidEmails();
        const QStringList validEmails = job.validEmails();

        if (!invalidEmails.isEmpty()) {
            QPointer<ConfirmAddressDialog> dlg = new ConfirmAddressDialog(parentWidget());
            dlg->setValidAddresses(validEmails);
            dlg->setInvalidAddresses(invalidEmails);
            if (dlg->exec()) {
                delete dlg;
                return true;
            } else {
                delete dlg;
                return false;
            }
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void ConfirmAddressInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mEnabled = grp.readEntry("Enabled", false);
    mHashSettings.clear();

    KIdentityManagement::IdentityManager manager(true);
    KIdentityManagement::IdentityManager::ConstIterator end = manager.end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = manager.begin(); it != end; ++it) {
        const uint identity = (*it).uoid();
        KConfigGroup identityGroup = grp.group(QStringLiteral("Confirm Address %1").arg(identity));
        ConfirmAddressSettings settings;
        settings.mDomains = identityGroup.readEntry("Domains", QStringList());
        settings.mWhiteLists = identityGroup.readEntry("Emails", QStringList());
        mHashSettings.insert(identity, settings);
    }
}
