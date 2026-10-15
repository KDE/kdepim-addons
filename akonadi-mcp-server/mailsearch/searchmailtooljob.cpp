/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "searchmailtooljob.h"
#include <KLocalizedString>

SearchMailToolJob::SearchMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

SearchMailToolJob::~SearchMailToolJob() = default;

bool SearchMailToolJob::canStart() const
{
    // TODO
    return false;
}

QString SearchMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Search string must be a non-empty string");
}

void SearchMailToolJob::startJob()
{
    // TODO
    deleteLater();
}

#include "moc_searchmailtooljob.cpp"
