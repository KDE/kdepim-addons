/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

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

PMailSettings::PMailSettings(const QString &filename)
    : mFileName(filename)
{
}

void PMailSettings::importSettings()
{
    if (QFileInfo::exists(mFileName)) {
        KConfig config(mFileName);

        const QStringList accountList = config.groupList().filter(QRegularExpression(QStringLiteral("WinPMail Identity - *")));
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
    QString personalNameStr = QStringLiteral("Personal name                             ");
    QString personalName;
    if (group.hasKey(personalNameStr)) {
        personalName = group.readEntry(personalNameStr);
        personalName.remove(0, 1); // Remove first space
    }
    KIdentityManagementCore::Identity *newIdentity = createIdentity(personalName);
    newIdentity->setFullName(personalName);
    newIdentity->setIdentityName(personalName);

    const QString emailStr = QStringLiteral("Internet E-mail Address                   ");
    if (group.hasKey(emailStr)) {
        QString email = group.readEntry(emailStr);
        email.remove(0, 1); // Remove first space
        newIdentity->setPrimaryEmailAddress(email);
    }
    const QString replytoStr = QStringLiteral("Default reply-to address                  ");
    if (group.hasKey(replytoStr)) {
        QString reply = group.readEntry(replytoStr);
        reply.remove(0, 1); // Remove first space
        newIdentity->setReplyToAddr(reply);
    }
    storeIdentity(newIdentity);
}
