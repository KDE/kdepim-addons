/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "openmailtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <KLocalizedString>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>

using namespace Qt::Literals::StringLiterals;

namespace
{
const QString kmailService = u"org.kde.kmail"_s;
}

OpenMailToolJob::OpenMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

OpenMailToolJob::~OpenMailToolJob() = default;

void OpenMailToolJob::setItemId(qint64 id)
{
    mItemId = id;
}

bool OpenMailToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0;
}

QString OpenMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer");
}

void OpenMailToolJob::startJob()
{
    // Asynchronous version of QDBusConnectionInterface::startService(), it doesn't block when KMail is not running
    QDBusMessage message =
        QDBusMessage::createMethodCall(u"org.freedesktop.DBus"_s, u"/org/freedesktop/DBus"_s, u"org.freedesktop.DBus"_s, u"StartServiceByName"_s);
    message << kmailService << 0U;
    auto watcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(message), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, &OpenMailToolJob::slotKMailStarted);
}

void OpenMailToolJob::slotKMailStarted(QDBusPendingCallWatcher *watcher)
{
    watcher->deleteLater();
    if (!hasToolCall()) {
        deleteLater();
        return;
    }
    if (watcher->isError()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Unable to start KMail:" << watcher->error().message();
        finish(i18n("Unable to start KMail: %1", watcher->error().message()), true);
        return;
    }
    QDBusMessage message = QDBusMessage::createMethodCall(kmailService, u"/KMail"_s, u"org.kde.kmail.kmail"_s, u"showMail"_s);
    message << mItemId;
    auto showWatcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(message), this);
    connect(showWatcher, &QDBusPendingCallWatcher::finished, this, &OpenMailToolJob::slotShowMailResult);
}

void OpenMailToolJob::slotShowMailResult(QDBusPendingCallWatcher *watcher)
{
    watcher->deleteLater();
    if (!hasToolCall()) {
        deleteLater();
        return;
    }
    const QDBusPendingReply<bool> reply = *watcher;
    if (reply.isError()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "showMail failed:" << reply.error().message();
        finish(i18n("Unable to open mail %1: %2", mItemId, reply.error().message()), true);
        return;
    }
    if (!reply.value()) {
        finish(i18n("Mail %1 not found or KMail main window is not available", mItemId), true);
        return;
    }
    finish(i18n("Mail %1 opened in KMail", mItemId));
}

#include "moc_openmailtooljob.cpp"
