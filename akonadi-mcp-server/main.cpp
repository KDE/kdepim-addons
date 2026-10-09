/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QCoreApplication>

#include <QCommandLineParser>

using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    const QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    const QCommandLineOption urlOption(u"url"_s, u"Url where server listens."_s, u"url"_s, u"http://127.0.0.1:8765/mcp"_s);
    parser.addOption(urlOption);
    parser.process(app);

    return app.exec();
}
