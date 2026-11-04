/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "forwardmailtooljob.h"
#include <KLocalizedString>
#include <QDBusMessage>
#include <QDBusPendingReply>

using namespace Qt::Literals::StringLiterals;

ForwardMailToolJob::ForwardMailToolJob(QObject *parent)
    : KMailDBusToolJobBase{parent}
{
}

ForwardMailToolJob::~ForwardMailToolJob() = default;

void ForwardMailToolJob::setItemId(qint64 id)
{
    mItemId = id;
}

void ForwardMailToolJob::setAsAttachment(bool asAttachment)
{
    mAsAttachment = asAttachment;
}

bool ForwardMailToolJob::canStart() const
{
    return KMailDBusToolJobBase::canStart() && mItemId >= 0;
}

QString ForwardMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer");
}

QDBusMessage ForwardMailToolJob::kmailMethodCall() const
{
    QDBusMessage message = createKMailMethodCall(u"forwardMail"_s);
    message << mItemId << mAsAttachment;
    return message;
}

QString ForwardMailToolJob::kmailCallErrorMessage(const QString &error) const
{
    return i18n("Unable to forward mail %1: %2", mItemId, error);
}

void ForwardMailToolJob::kmailCallFinished(const QDBusPendingCall &reply)
{
    const QDBusPendingReply<bool> forwardMailReply = reply;
    if (!forwardMailReply.value()) {
        finish(i18n("Unable to forward mail %1: KMail main window is not available", mItemId), true);
        return;
    }
    finish(i18n("Forward composer opened in KMail for mail %1", mItemId));
}

#include "moc_forwardmailtooljob.cpp"
