/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactgroupexpandtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/ContactGroupSearchJob>
#include <KJob>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

ContactGroupExpandToolJob::ContactGroupExpandToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

ContactGroupExpandToolJob::~ContactGroupExpandToolJob() = default;

void ContactGroupExpandToolJob::setGroupName(const QString &str)
{
    mSearchString = str;
}

bool ContactGroupExpandToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mSearchString.isEmpty();
}

QString ContactGroupExpandToolJob::invalidArgumentsMessage() const
{
    return i18n("Search string must be a non-empty string");
}

void ContactGroupExpandToolJob::startJob()
{
    auto searchJob = new Akonadi::ContactGroupSearchJob(this);
    searchJob->setQuery(Akonadi::ContactGroupSearchJob::Name, mSearchString, Akonadi::ContactGroupSearchJob::ContainsMatch);
    connect(searchJob, &KJob::result, this, &ContactGroupExpandToolJob::slotResult);
    setCurrentJob(searchJob);
}

void ContactGroupExpandToolJob::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact group search failed: %1"))) {
        return;
    }
    mContactGroups = qobject_cast<Akonadi::ContactGroupSearchJob *>(job)->contactGroups();
    if (mContactGroups.isEmpty()) {
        finish(i18n("No contact group found for \"%1\"", mSearchString));
        return;
    }
    mEntries.reserve(mContactGroups.count());
    expandNextGroup();
}

void ContactGroupExpandToolJob::expandNextGroup()
{
    if (!hasToolCall()) {
        deleteLater();
        return;
    }
    if (mContactGroups.isEmpty()) {
        finish(mEntries.join(u'\n'));
        return;
    }
    auto expandJob = new Akonadi::ContactGroupExpandJob(mContactGroups.constFirst(), this);
    connect(expandJob, &KJob::result, this, &ContactGroupExpandToolJob::slotExpandResult);
    setCurrentJob(expandJob);
    expandJob->start();
}

void ContactGroupExpandToolJob::slotExpandResult(KJob *job)
{
    const KContacts::ContactGroup contactGroup = mContactGroups.takeFirst();
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact group expand failed:" << contactGroup.name() << job->errorString();
        mEntries.append(i18n("%1: expand failed: %2", contactGroup.name(), job->errorString()));
        expandNextGroup();
        return;
    }
    const KContacts::Addressee::List contacts = qobject_cast<Akonadi::ContactGroupExpandJob *>(job)->contacts();
    QStringList lines{contactGroup.name()};
    lines.reserve(contacts.count() + 1);
    for (const KContacts::Addressee &contact : contacts) {
        if (contact.preferredEmail().isEmpty()) {
            lines.append(contact.realName());
        } else {
            lines.append(contact.fullEmail());
        }
    }
    mEntries.append(lines.join(u"\n  "_s));
    expandNextGroup();
}

#include "moc_contactgroupexpandtooljob.cpp"
