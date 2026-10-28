/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QCoreApplication>

#include "akonadimcpprotocolmanager.h"
#include <KLocalizedString>
#include <QCommandLineParser>

using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    const QCoreApplication app(argc, argv);
    // KJob holds a QEventLoopLocker: don't quit when last Akonadi job finishes
    QCoreApplication::setQuitLockEnabled(false);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    const QCommandLineOption urlOption(u"url"_s, i18nc("@info:shell", "Url where server listens."), u"url"_s);
    parser.addOption(urlOption);
    parser.process(app);

    AkonadiMcpProtocolManager manager;
    if (!manager.start(parser.value(urlOption))) {
        return 0;
    }

    return app.exec();
}
