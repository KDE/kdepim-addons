/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "openmailtooljob.h"
#include <KLocalizedString>
#include <QDBusMessage>
#include <QDBusPendingReply>

using namespace Qt::Literals::StringLiterals;

OpenMailToolJob::OpenMailToolJob(QObject *parent)
    : KMailDBusToolJobBase{parent}
{
}

OpenMailToolJob::~OpenMailToolJob() = default;

void OpenMailToolJob::setItemId(qint64 id)
{
    mItemId = id;
}

bool OpenMailToolJob::canStart() const
{
    return KMailDBusToolJobBase::canStart() && mItemId >= 0;
}

QString OpenMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer");
}

QDBusMessage OpenMailToolJob::kmailMethodCall() const
{
    QDBusMessage message = createKMailMethodCall(u"showMail"_s);
    message << mItemId;
    return message;
}

QString OpenMailToolJob::kmailCallErrorMessage(const QString &error) const
{
    return i18n("Unable to open mail %1: %2", mItemId, error);
}

void OpenMailToolJob::kmailCallFinished(const QDBusPendingCall &reply)
{
    const QDBusPendingReply<bool> showMailReply = reply;
    if (!showMailReply.value()) {
        finish(i18n("Mail %1 not found or KMail main window is not available", mItemId), true);
        return;
    }
    finish(i18n("Mail %1 displayed in a read-only KMail viewer, it can't be modified there", mItemId));
}

#include "moc_openmailtooljob.cpp"
