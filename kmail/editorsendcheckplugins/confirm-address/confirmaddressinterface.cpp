/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmaddresscheckjob.h"
#include "confirmaddressconfigurewidget.h"
#include "confirmaddressdialog.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QPointer>

#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <MessageComposer/AliasesExpandJob>
#include <PimCommon/PimUtil>
namespace
{
static const char myConfigGroupName[] = "Confirm Address";
}
ConfirmAddressInterface::ConfirmAddressInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent)
{
}

ConfirmAddressInterface::~ConfirmAddressInterface() = default;

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
    // not configured => validate it.
    const ConfirmAddressSettings settings = mHashSettings.value(params.identity());
    if (settings.mDomains.isEmpty() && settings.mWhiteLists.isEmpty()) {
        return true;
    }
    const QStringList emails = PimCommon::Util::generateEmailList(lst);
#if 0
    MessageComposer::AliasesExpandJob job(params.addresses().join(QLatin1StringView(", ")), params.defaultDomain(), this);
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
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    KConfigGroup identityGroup = grp.group(u"Confirm Address %1"_s.arg(currentIdentity));
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
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    mHashSettings.clear();

    KIdentityManagementCore::IdentityManager *im = KIdentityManagementCore::IdentityManager::self();
    KIdentityManagementCore::IdentityManager::ConstIterator end = im->end();
    for (KIdentityManagementCore::IdentityManager::ConstIterator it = im->begin(); it != end; ++it) {
        const uint identity = (*it).uoid();
        KConfigGroup identityGroup = grp.group(u"Confirm Address %1"_s.arg(identity));
        ConfirmAddressSettings settings;
        settings.mDomains = identityGroup.readEntry("Domains", QStringList());
        settings.mWhiteLists = identityGroup.readEntry("Emails", QStringList());
        settings.mRejectedDomain = identityGroup.readEntry("RejectDomain", false);

        mHashSettings.insert(identity, settings);
    }
}

#include "moc_confirmaddressinterface.cpp"
