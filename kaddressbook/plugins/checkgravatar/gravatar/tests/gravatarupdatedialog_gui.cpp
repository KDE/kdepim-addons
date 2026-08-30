/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "../widgets/gravatarupdatedialog.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << u"email"_s, u"Email address"_s, u"emailaddress"_s));

    parser.process(app);
    QString email;
    if (!parser.value(u"email"_s).isEmpty()) {
        email = parser.value(u"email"_s);
    }

    KABGravatar::GravatarUpdateDialog dlg;
    dlg.setEmail(email);
    dlg.show();

    app.exec();
    return 0;
}
