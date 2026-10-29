/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QCoreApplication>

#include "akonadimcpprotocolmanager.h"
#include <KAboutData>
#include <KCrash>
#include <KDBusService>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QDBusConnection>

using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    const QCoreApplication app(argc, argv);
    // KJob holds a QEventLoopLocker: don't quit when last Akonadi job finishes
    QCoreApplication::setQuitLockEnabled(false);

    KAboutData aboutData(u"akonadimcpprotocol"_s,
                         i18n("Akonadi MCP Server"),
                         u"1.0"_s,
                         i18n("Akonadi MCP Server"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2026 Laurent Montel"));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);
    aboutData.setOrganizationDomain("kde.org"_ba);

    KAboutData::setApplicationData(aboutData);
    KCrash::initialize();

    QCommandLineParser parser;
    const QCommandLineOption urlOption(u"url"_s, i18nc("@info:shell", "Url where server listens."), u"url"_s);
    parser.addOption(urlOption);
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    const KDBusService service(KDBusService::Unique);

    AkonadiMcpProtocolManager manager;
    if (!manager.start(parser.value(urlOption))) {
        return 0;
    }
    QDBusConnection::sessionBus().registerObject(u"/"_s, &manager, QDBusConnection::ExportScriptableSlots);

    return app.exec();
}
