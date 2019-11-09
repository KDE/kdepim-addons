/*
    Copyright (c) 2010 Stephen Kelly <steveire@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

// READ THE README FILE

#include <KLocalizedString>
#include <KAboutData>

#include <QApplication>
#include <QCommandLineParser>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    KAboutData aboutData(QStringLiteral("etm_usage"),
                         i18n("ETM Test application"),
                         QStringLiteral("0.99"),
                         i18n("Test app for EntityTreeModel"),
                         KAboutLicense::GPL,
                         QStringLiteral("https://community.kde.org/KDE_PIM/Akonadi/"));
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("akonadi")));
    aboutData.addAuthor(i18n("Stephen Kelly"), i18n("Author"), QStringLiteral("steveire@gmail.com"));

    QApplication app(argc, argv);
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);
    app.setQuitOnLastWindowClosed(true);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
