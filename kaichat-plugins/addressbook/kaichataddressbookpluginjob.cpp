/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginjob.h"
#include "kaichat_addressbookplugin_debug.h"
#include "kaichataddressbookpluginutils.h"
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

    Q_EMIT toolInProgress(i18n("Get Email..."));
    QString result;
    const QStringList lst = requiredArguments();
    for (const auto &arg : lst) {
        for (const auto &resultTool : std::as_const(mToolArguments)) {
            if (resultTool.keyTool == arg) {
                const QString value = resultTool.value;
                if (arg == "addressbookinfo"_L1) {
                    const KAIChatAddressBookPluginUtils::AddressBookEnum typeAddressBook = KAIChatAddressBookPluginUtils::convertStringToAddressBookEnum(value);
                    switch (typeAddressBook) {
                    case KAIChatAddressBookPluginUtils::AddressBookEnum::Email:
                        // TODO result = i18n("Current time is %1", QLocale().toString(QTime::currentTime()));
                        break;
                    case KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown:
                        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid addressbook argument" << value;
                        break;
                    }
                }
            }
        }
    }

    qDebug() << " toolArguments " << toolArguments();
    Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
    deleteLater();
}

#include "moc_kaichataddressbookpluginjob.cpp"
