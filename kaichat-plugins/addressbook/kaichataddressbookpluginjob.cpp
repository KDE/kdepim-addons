/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginjob.h"
#include "kaichat_addressbookplugin_debug.h"
#include "kaichataddressbookpluginutils.h"
#include <Akonadi/ContactSearchJob>
#include <KJob>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
KAIChatAddressBookPluginJob::KAIChatAddressBookPluginJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextToolPluginJob{parent}
{
}

KAIChatAddressBookPluginJob::~KAIChatAddressBookPluginJob() = default;

void KAIChatAddressBookPluginJob::start()
{
    if (!canStart()) {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << " Impossible to start KAIChatAddressBookPluginJob" << *this;
        deleteLater();
        return;
    }

    qDebug() << " toolArguments " << toolArguments();
    Q_EMIT toolInProgress(i18n("Get Email..."));
    QString userName;
    const QStringList lst = requiredArguments();
    KAIChatAddressBookPluginUtils::AddressBookEnum typeAddressBook = KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown;
    for (const auto &arg : lst) {
        for (const auto &resultTool : std::as_const(mToolArguments)) {
            if (resultTool.keyTool == arg) {
                const QString value = resultTool.value;
                if (arg == "addressbookinfo"_L1) {
                    typeAddressBook = KAIChatAddressBookPluginUtils::convertStringToAddressBookEnum(value);
                } else if (arg == "username"_L1) {
                    userName = value;
                } else {
                    qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid argument : " << value;
                }
            }
        }
    }
    if (typeAddressBook == KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown) {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid addressbook argument";
        deleteLater();
        return;
    }

    auto job = new Akonadi::ContactSearchJob(this);
    job->setProperty("userName", userName.toUtf8());
    job->setQuery(Akonadi::ContactSearchJob::Email, userName, Akonadi::ContactSearchJob::ExactMatch);
    connect(job, &KJob::result, this, [this, typeAddressBook](KJob *job) {
        const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);
        QString result;
        if (searchJob->contacts().isEmpty()) {
            result = i18n("No Contact found in addressbook for %1", job->property("userName").toString());
        } else {
            const KContacts::Addressee contact = searchJob->contacts().constFirst();
            qDebug() << " contact " << contact.toString();
            switch (typeAddressBook) {
            case KAIChatAddressBookPluginUtils::AddressBookEnum::Email: {
                const QString preferedEmail = contact.preferredEmail();
                if (preferedEmail.isEmpty()) {
                    result = i18n("No preferred email found for %1", job->property("userName").toString());
                } else {
                    result = i18n("The preferred email for %1 is %2", job->property("userName").toString(), preferedEmail);
                }
                break;
            }
            case KAIChatAddressBookPluginUtils::AddressBookEnum::Birthday: {
                const QString birthday = contact.birthday().toString();
                if (birthday.isEmpty()) {
                    result = i18n("No Birthday found for %1", job->property("userName").toString());
                } else {
                    result = i18n("Birthday for %1 is %2", job->property("userName").toString(), birthday);
                }
                break;
            }
            case KAIChatAddressBookPluginUtils::AddressBookEnum::Address: {
                const KContacts::Address::List addresses = contact.addresses();
                QStringList lst;
                for (const auto &addr : addresses) {
                    lst << addr.formatted(KContacts::AddressFormatStyle::Postal);
                }
                if (lst.isEmpty()) {
                    result = i18n("No Address found for %1", job->property("userName").toString());
                } else {
                    result = i18n("Address found for %1 is %2", job->property("userName").toString(), lst.join(u'\n'));
                }
                break;
            }
            case KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown:
                break;
            }
        }
        Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
        deleteLater();
    });
}

#include "moc_kaichataddressbookpluginjob.cpp"
