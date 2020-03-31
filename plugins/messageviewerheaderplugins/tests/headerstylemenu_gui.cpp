/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "headerstylemenu_gui.h"
#include <MessageViewer/HeaderStyleMenuManager>
#include <QStandardPaths>

#include <QApplication>
#include <QCommandLineParser>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

#include <KActionCollection>
#include <QTextEdit>
#include <KActionMenu>
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/HeaderStyle>
#include <MessageViewer/HeaderStylePlugin>

HeaderStyleMenuTest::HeaderStyleMenuTest(QWidget *parent)
    : QWidget(parent)
{
    QMenuBar *menu = new QMenuBar(this);
    QVBoxLayout *hbox = new QVBoxLayout(this);
    hbox->addWidget(menu);
    MessageViewer::HeaderStyleMenuManager *manager = new MessageViewer::HeaderStyleMenuManager(new KActionCollection(this), this);
    menu->addAction(manager->menu());
    mTextEdit = new QTextEdit(this);
    mTextEdit->setReadOnly(true);
    hbox->addWidget(mTextEdit);
    connect(manager, &MessageViewer::HeaderStyleMenuManager::styleChanged, this, &HeaderStyleMenuTest::styleChanged);
    manager->readConfig();
}

HeaderStyleMenuTest::~HeaderStyleMenuTest()
{
}

void HeaderStyleMenuTest::styleChanged(MessageViewer::HeaderStylePlugin *plugin)
{
    mTextEdit->append(QStringLiteral("strategy: %1, headerstyle: %2").arg(QLatin1String(plugin->headerStrategy()->name()))
                      .arg(QLatin1String(plugin->headerStyle()->name())));
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    HeaderStyleMenuTest *w = new HeaderStyleMenuTest();
    w->resize(800, 200);
    w->show();
    app.exec();
    delete w;
    return 0;
}
