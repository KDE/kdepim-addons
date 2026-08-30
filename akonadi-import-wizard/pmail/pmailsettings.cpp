/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pmailsettings.h"
#include <ImportWizard/ImportWizardUtil>

#include <MailCommon/MailUtil>
#include <MailTransport/TransportManager>

#include <KIdentityManagementCore/Identity>

#include <KConfig>
#include <KConfigGroup>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
using namespace Qt::Literals::StringLiterals;

PMailSettings::PMailSettings(const QString &filename)
    : mFileName(filename)
{
}

void PMailSettings::importSettings()
{
    if (QFileInfo::exists(mFileName)) {
        KConfig config(mFileName);

        const QStringList accountList = config.groupList().filter(QRegularExpression(u"WinPMail Identity - *"_s));
        const QStringList::const_iterator end(accountList.constEnd());
        for (QStringList::const_iterator it = accountList.constBegin(); it != end; ++it) {
            KConfigGroup group = config.group(*it);
            readIdentity(group);
        }
    }
}

PMailSettings::~PMailSettings()
{
}

void PMailSettings::readIdentity(const KConfigGroup &group)
{
    QString personalNameStr = u"Personal name                             "_s;
    QString personalName;
    if (group.hasKey(personalNameStr)) {
        personalName = group.readEntry(personalNameStr);
        personalName.remove(0, 1); // Remove first space
    }
    KIdentityManagementCore::Identity *newIdentity = createIdentity(personalName);
    newIdentity->setFullName(personalName);
    newIdentity->setIdentityName(personalName);

    const QString emailStr = u"Internet E-mail Address                   "_s;
    if (group.hasKey(emailStr)) {
        QString email = group.readEntry(emailStr);
        email.remove(0, 1); // Remove first space
        newIdentity->setPrimaryEmailAddress(email);
    }
    const QString replytoStr = u"Default reply-to address                  "_s;
    if (group.hasKey(replytoStr)) {
        QString reply = group.readEntry(replytoStr);
        reply.remove(0, 1); // Remove first space
        newIdentity->setReplyToAddr(reply);
    }
    storeIdentity(newIdentity);
}
