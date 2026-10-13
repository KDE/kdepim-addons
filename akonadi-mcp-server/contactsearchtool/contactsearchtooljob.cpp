/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactsearchtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <KLocalizedString>

ContactSearchToolJob::ContactSearchToolJob(QObject *parent)
    : QObject{parent}
{
}

ContactSearchToolJob::~ContactSearchToolJob() = default;

void ContactSearchToolJob::setNameOrEmail(const QString &str)
{
    mSearchString = str;
}

bool ContactSearchToolJob::canStart() const
{
    return !mSearchString.isEmpty();
}

void ContactSearchToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ContactSearchToolJob can't start";
        Q_EMIT error(i18n("Search string must be a non-empty string"));
        deleteLater();
        return;
    }
    // TODO

    deleteLater();
}