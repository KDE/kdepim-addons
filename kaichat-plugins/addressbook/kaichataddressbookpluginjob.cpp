/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginjob.h"
#include "kaichat_addressbookplugin_debug.h"

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

    deleteLater();
    // TODO
    Q_EMIT finished({}, {}, {}, {});
    // TODO
}

#include "moc_kaichataddressbookpluginjob.cpp"
