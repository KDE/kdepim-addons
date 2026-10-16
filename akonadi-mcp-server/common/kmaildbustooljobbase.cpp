/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kmaildbustooljobbase.h"
#include "akonadimcpprotocol_debug.h"
#include <KLocalizedString>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>

using namespace Qt::Literals::StringLiterals;

namespace
{
const QString kmailService = u"org.kde.kmail"_s;
}

KMailDBusToolJobBase::KMailDBusToolJobBase(QObject *parent)
    : ToolJobBase{parent}
{
}

KMailDBusToolJobBase::~KMailDBusToolJobBase() = default;

QDBusMessage KMailDBusToolJobBase::createKMailMethodCall(const QString &method)
{
    return QDBusMessage::createMethodCall(kmailService, u"/KMail"_s, u"org.kde.kmail.kmail"_s, method);
}

void KMailDBusToolJobBase::startJob()
{
    // Asynchronous version of QDBusConnectionInterface::startService(), it doesn't block when KMail is not running
    QDBusMessage message =
        QDBusMessage::createMethodCall(u"org.freedesktop.DBus"_s, u"/org/freedesktop/DBus"_s, u"org.freedesktop.DBus"_s, u"StartServiceByName"_s);
    message << kmailService << 0U;
    auto watcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(message), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, &KMailDBusToolJobBase::slotKMailStarted);
}

void KMailDBusToolJobBase::slotKMailStarted(QDBusPendingCallWatcher *watcher)
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
    auto callWatcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(kmailMethodCall()), this);
    connect(callWatcher, &QDBusPendingCallWatcher::finished, this, &KMailDBusToolJobBase::slotKMailCallFinished);
}

void KMailDBusToolJobBase::slotKMailCallFinished(QDBusPendingCallWatcher *watcher)
{
    watcher->deleteLater();
    if (!hasToolCall()) {
        deleteLater();
        return;
    }
    if (watcher->isError()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << metaObject()->className() << "D-Bus call failed:" << watcher->error().message();
        finish(kmailCallErrorMessage(watcher->error().message()), true);
        return;
    }
    kmailCallFinished(*watcher);
}

#include "moc_kmaildbustooljobbase.cpp"
