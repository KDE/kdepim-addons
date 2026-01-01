/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountpluginopenfolderjob.h"
#include "checkfoldersizeaccount_debug.h"

#include <KLocalizedString>

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>

CheckFolderSizeAccountPluginOpenFolderJob::CheckFolderSizeAccountPluginOpenFolderJob(const QString &identifier, QObject *parent)
    : KJob{parent}
    , mIdentifer(identifier)
{
}

CheckFolderSizeAccountPluginOpenFolderJob::~CheckFolderSizeAccountPluginOpenFolderJob() = default;

void CheckFolderSizeAccountPluginOpenFolderJob::start()
{
    const qint64 identifier = mIdentifer.toLong();
    if (identifier < 0) {
        emitResult();
        return;
    }

    const QString kmailInterface = QStringLiteral("org.kde.kmail");
    auto startReply = QDBusConnection::sessionBus().interface()->startService(kmailInterface);
    if (!startReply.isValid()) {
        qCDebug(KMAIL_CHECKFOLDERSIZEACCOUNT_PLUGIN_LOG) << "Can not start kmail";
        setError(UserDefinedError);
        setErrorText(i18n("Unable to start KMail application."));
        emitResult();
        return;
    }

    QDBusInterface kmail(kmailInterface, QStringLiteral("/KMail"), QStringLiteral("org.kde.kmail.kmail"));
    if (kmail.isValid()) {
        kmail.call(QStringLiteral("selectFolder"), mIdentifer);
    } else {
        qCWarning(KMAIL_CHECKFOLDERSIZEACCOUNT_PLUGIN_LOG) << "Impossible to access the DBus interface";
    }

    emitResult();
}

#include "moc_checkfoldersizeaccountpluginopenfolderjob.cpp"
