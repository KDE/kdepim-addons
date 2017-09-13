/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
#include "../widgets/gravatarupdatedialog.h"

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
