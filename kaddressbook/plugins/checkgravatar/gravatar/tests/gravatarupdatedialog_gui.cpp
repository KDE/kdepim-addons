/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "../widgets/gravatarupdatedialog.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("email"), QStringLiteral("Email address"), QStringLiteral("emailaddress")));

    parser.process(app);
    QString email;
    if (!parser.value(QStringLiteral("email")).isEmpty()) {
        email = parser.value(QStringLiteral("email"));
    }

    KABGravatar::GravatarUpdateDialog dlg;
    dlg.setEmail(email);
    dlg.show();

    app.exec();
    return 0;
}
