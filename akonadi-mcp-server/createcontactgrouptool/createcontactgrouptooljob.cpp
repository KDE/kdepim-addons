/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "createcontactgrouptooljob.h"
#include <KLocalizedString>

CreateContactGroupToolJob::CreateContactGroupToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

CreateContactGroupToolJob::~CreateContactGroupToolJob() = default;

void CreateContactGroupToolJob::setName(const QString &name)
{
    mName = name;
}

void CreateContactGroupToolJob::setContactIds(const QList<Akonadi::Item::Id> &contactIds)
{
    mContactIds = contactIds;
}

void CreateContactGroupToolJob::setEmails(const QStringList &emails)
{
    mEmails = emails;
}

void CreateContactGroupToolJob::setAddressBookId(Akonadi::Collection::Id id)
{
    mAddressBookId = id;
}

bool CreateContactGroupToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mName.isEmpty();
}

QString CreateContactGroupToolJob::invalidArgumentsMessage() const
{
    return i18n("Contact group name is empty");
}

void CreateContactGroupToolJob::startJob()
{
    // TODO:
    finish(i18n("Creating a contact group is not implemented yet"), true);
}

#include "moc_createcontactgrouptooljob.cpp"
