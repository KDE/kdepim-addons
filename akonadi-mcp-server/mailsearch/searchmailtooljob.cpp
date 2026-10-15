/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "searchmailtooljob.h"
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemSearchJob>
#include <Akonadi/MessageParts>
#include <Akonadi/SearchQuery>
#include <KJob>
#include <KLocalizedString>
#include <KMime/Message>
#include <QDateTime>

#include <algorithm>

using namespace Qt::Literals::StringLiterals;

namespace
{
struct MailEntry {
    QDateTime date;
    QString text;
};
}

SearchMailToolJob::SearchMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

SearchMailToolJob::~SearchMailToolJob() = default;

void SearchMailToolJob::setSearchString(const QString &str)
{
    mSearchString = str;
}

void SearchMailToolJob::setSearchField(SearchField field)
{
    mSearchField = field;
}

void SearchMailToolJob::setLimit(int limit)
{
    mLimit = limit;
}

bool SearchMailToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mSearchString.isEmpty() && mLimit > 0;
}

QString SearchMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Search string must be a non-empty string");
}

void SearchMailToolJob::startJob()
{
    Akonadi::SearchQuery query(Akonadi::SearchTerm::RelOr);
    switch (mSearchField) {
    case SearchField::All:
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::Subject, mSearchString, Akonadi::SearchTerm::CondContains));
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderFrom, mSearchString, Akonadi::SearchTerm::CondContains));
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderTo, mSearchString, Akonadi::SearchTerm::CondContains));
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderCC, mSearchString, Akonadi::SearchTerm::CondContains));
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::Body, mSearchString, Akonadi::SearchTerm::CondContains));
        break;
    case SearchField::Subject:
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::Subject, mSearchString, Akonadi::SearchTerm::CondContains));
        break;
    case SearchField::From:
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderFrom, mSearchString, Akonadi::SearchTerm::CondContains));
        break;
    case SearchField::To:
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderTo, mSearchString, Akonadi::SearchTerm::CondContains));
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::HeaderCC, mSearchString, Akonadi::SearchTerm::CondContains));
        break;
    case SearchField::Body:
        query.addTerm(Akonadi::EmailSearchTerm(Akonadi::EmailSearchTerm::Body, mSearchString, Akonadi::SearchTerm::CondContains));
        break;
    }
    query.setLimit(mLimit);

    auto searchJob = new Akonadi::ItemSearchJob(query, this);
    searchJob->setMimeTypes({KMime::Message::mimeType()});
    searchJob->fetchScope().fetchPayloadPart(Akonadi::MessagePart::Envelope);
    searchJob->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);
    connect(searchJob, &KJob::result, this, &SearchMailToolJob::slotResult);
    setCurrentJob(searchJob);
}

void SearchMailToolJob::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail search failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemSearchJob *>(job)->items();
    QList<MailEntry> entries;
    entries.reserve(items.count());
    for (const Akonadi::Item &item : items) {
        if (!item.hasPayload<std::shared_ptr<KMime::Message>>()) {
            continue;
        }
        const std::shared_ptr<const KMime::Message> message = item.payload<std::shared_ptr<KMime::Message>>();
        MailEntry entry;
        QStringList lines;
        if (const auto subject = message->subject(); subject && !subject->isEmpty()) {
            lines.append(subject->asUnicodeString());
        } else {
            lines.append(i18n("(No subject)"));
        }
        if (const auto from = message->from(); from && !from->isEmpty()) {
            lines.append(u"From: "_s + from->asUnicodeString());
        }
        if (const auto to = message->to(); to && !to->isEmpty()) {
            lines.append(u"To: "_s + to->asUnicodeString());
        }
        if (const auto cc = message->cc(); cc && !cc->isEmpty()) {
            lines.append(u"Cc: "_s + cc->asUnicodeString());
        }
        if (const auto date = message->date(); date && !date->isEmpty()) {
            entry.date = date->dateTime();
            lines.append(u"Date: "_s + entry.date.toLocalTime().toString(Qt::ISODate));
        }
        if (const Akonadi::Collection collection = item.parentCollection(); !collection.displayName().isEmpty()) {
            lines.append(u"Folder: "_s + collection.displayName());
        }
        lines.append(u"Id: %1"_s.arg(item.id()));
        entry.text = lines.join(u"\n  "_s);
        entries.append(std::move(entry));
    }
    if (entries.isEmpty()) {
        finish(i18n("No mail found for \"%1\"", mSearchString));
        return;
    }
    std::sort(entries.begin(), entries.end(), [](const MailEntry &left, const MailEntry &right) {
        return left.date > right.date;
    });
    if (entries.count() > mLimit) {
        entries.resize(mLimit);
    }
    QStringList texts;
    texts.reserve(entries.count());
    for (const MailEntry &entry : std::as_const(entries)) {
        texts.append(entry.text);
    }
    finish(texts.join(u'\n'));
}

#include "moc_searchmailtooljob.cpp"
