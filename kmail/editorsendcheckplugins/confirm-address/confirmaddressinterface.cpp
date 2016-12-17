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
#include <QDebug>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KEmailAddress>

#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>
#include <MessageComposer/AliasesExpandJob>

ConfirmAddressInterface::ConfirmAddressInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent)
{
}

ConfirmAddressInterface::~ConfirmAddressInterface()
{

}

bool ConfirmAddressInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
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
    if (lst.isEmpty()) {
        return true;
    }
    // not configurated => validate it.
    const ConfirmAddressSettings settings = mHashSettings.value(params.identity());
    if (settings.mDomains.isEmpty() && settings.mWhiteLists.isEmpty()) {
        return true;
    }
    const QString str = lst.join(QStringLiteral(", "));
    const QStringList emails = KEmailAddress::splitAddressList(str);
#if 0
    MessageComposer::AliasesExpandJob job(params.addresses().join(QStringLiteral(", ")), params.defaultDomain(), this);
    if (job.exec()) {
        emails = job.emailAddressOnly();
    }
#endif
    ConfirmAddressCheckJob job;
    job.setCheckSettings(settings.mDomains, settings.mWhiteLists, settings.mRejectedDomain);
    job.setAddressList(emails);
    job.start();

    const QStringList invalidEmails = job.invalidEmails();
    const QStringList validEmails = job.validEmails();

    if (!invalidEmails.isEmpty()) {
        QPointer<ConfirmAddressDialog> dlg = new ConfirmAddressDialog(parentWidget());
        connect(dlg.data(), &ConfirmAddressDialog::addWhileListEmails, this, &ConfirmAddressInterface::slotAddWhiteListEmails);
        dlg->setCurrentIdentity(params.identity());
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
}

void ConfirmAddressInterface::slotAddWhiteListEmails(const QStringList &lst, uint currentIdentity)
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    KConfigGroup identityGroup = grp.group(QStringLiteral("Confirm Address %1").arg(currentIdentity));
    QStringList oldWhiteList = identityGroup.readEntry("Emails", QStringList());
    for (const QString &email : lst) {
        if (!oldWhiteList.contains(email)) {
            oldWhiteList.append(email);
        }
    }
    identityGroup.writeEntry("Emails", oldWhiteList);
    identityGroup.sync();
    Q_EMIT forceReloadConfig();
}

void ConfirmAddressInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mHashSettings.clear();

    KIdentityManagement::IdentityManager *im = KIdentityManagement::IdentityManager::self();
    KIdentityManagement::IdentityManager::ConstIterator end = im->end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = im->begin(); it != end; ++it) {
        const uint identity = (*it).uoid();
        KConfigGroup identityGroup = grp.group(QStringLiteral("Confirm Address %1").arg(identity));
        ConfirmAddressSettings settings;
        settings.mDomains = identityGroup.readEntry("Domains", QStringList());
        settings.mWhiteLists = identityGroup.readEntry("Emails", QStringList());
        settings.mRejectedDomain = identityGroup.readEntry("RejectDomain", false);

        mHashSettings.insert(identity, settings);
    }
}
