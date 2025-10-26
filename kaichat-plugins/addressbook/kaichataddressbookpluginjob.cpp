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
    QString result;
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
    switch (typeAddressBook) {
    case KAIChatAddressBookPluginUtils::AddressBookEnum::Email: {
        auto job = new Akonadi::ContactSearchJob(this);
        job->setQuery(Akonadi::ContactSearchJob::Email, userName, Akonadi::ContactSearchJob::ExactMatch);
        connect(job, &KJob::result, this, &KAIChatAddressBookPluginJob::slotContactSearchDone);
    } break;
    case KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown:
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid addressbook argument";
        deleteLater();
        break;
    }
#if 0
    Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
    deleteLater();
#endif
}

void KAIChatAddressBookPluginJob::slotContactSearchDone(KJob *job)
{
    const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);

    if (searchJob->contacts().isEmpty()) {
        // TODO
        Q_EMIT finished(i18n("No Contact found in addressbook for <username>"), mMessageUuid, mChatId, mToolIdentifier);
    } else {
        const KContacts::Addressee contact = searchJob->contacts().constFirst();
        // TODO
        // TODO Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
    }
    deleteLater();
}

#include "moc_kaichataddressbookpluginjob.cpp"
