/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
#include <KActionMenu>
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/HeaderStyle>
#include <MessageViewer/HeaderStylePlugin>
#include <QTextEdit>

HeaderStyleMenuTest::HeaderStyleMenuTest(QWidget *parent)
    : QWidget(parent)
{
    auto menu = new QMenuBar(this);
    auto hbox = new QVBoxLayout(this);
    hbox->addWidget(menu);
    auto manager = new MessageViewer::HeaderStyleMenuManager(new KActionCollection(this), this);
    menu->addAction(manager->menu());
    mTextEdit = new QTextEdit(this);
    mTextEdit->setReadOnly(true);
    hbox->addWidget(mTextEdit);
    connect(manager, &MessageViewer::HeaderStyleMenuManager::styleChanged, this, &HeaderStyleMenuTest::styleChanged);
    manager->readConfig();
}

HeaderStyleMenuTest::~HeaderStyleMenuTest() = default;

void HeaderStyleMenuTest::styleChanged(MessageViewer::HeaderStylePlugin *plugin)
{
    mTextEdit->append(
        QStringLiteral("strategy: %1, headerstyle: %2").arg(QLatin1String(plugin->headerStrategy()->name())).arg(QLatin1String(plugin->headerStyle()->name())));
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new HeaderStyleMenuTest();
    w->resize(800, 200);
    w->show();
    app.exec();
    delete w;
    return 0;
}
