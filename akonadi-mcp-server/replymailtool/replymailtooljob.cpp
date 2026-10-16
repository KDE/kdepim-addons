/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "replymailtooljob.h"
#include <KLocalizedString>
#include <QDBusMessage>
#include <QDBusPendingReply>

using namespace Qt::Literals::StringLiterals;

ReplyMailToolJob::ReplyMailToolJob(QObject *parent)
    : KMailDBusToolJobBase{parent}
{
}

ReplyMailToolJob::~ReplyMailToolJob() = default;

void ReplyMailToolJob::setItemId(qint64 id)
{
    mItemId = id;
}

void ReplyMailToolJob::setReplyStrategy(ReplyStrategy strategy)
{
    mReplyStrategy = strategy;
}

bool ReplyMailToolJob::canStart() const
{
    // KMail rejects ReplyNone
    return KMailDBusToolJobBase::canStart() && mItemId >= 0 && mReplyStrategy != ReplyStrategy::ReplyNone;
}

QString ReplyMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer and reply strategy must be smart, author, list or all");
}

QDBusMessage ReplyMailToolJob::kmailMethodCall() const
{
    QDBusMessage message = createKMailMethodCall(u"replyMailWithStrategy"_s);
    message << mItemId << static_cast<int>(mReplyStrategy);
    return message;
}

QString ReplyMailToolJob::kmailCallErrorMessage(const QString &error) const
{
    return i18n("Unable to reply to mail %1: %2", mItemId, error);
}

void ReplyMailToolJob::kmailCallFinished(const QDBusPendingCall &reply)
{
    const QDBusPendingReply<bool> replyMailReply = reply;
    if (!replyMailReply.value()) {
        finish(i18n("Unable to reply to mail %1: KMail main window is not available", mItemId), true);
        return;
    }
    finish(i18n("Reply composer opened in KMail for mail %1", mItemId));
}

#include "moc_replymailtooljob.cpp"
