/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "adblockautomaticruleslistwidget_gui.h"
#include "../widgets/adblockautomaticruleslistwidget.h"

#include <QCommandLineParser>
#include <QApplication>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QFileDialog>
AdBlockAutomaticRulesListWidgetTest::AdBlockAutomaticRulesListWidgetTest(const QString &fileName, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    QFile localFile(fileName);
    QString adblockList;
    if (localFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        adblockList = QString::fromLatin1(localFile.readAll());
    }
    AdBlock::AdBlockAutomaticRulesListWidget *list = new AdBlock::AdBlockAutomaticRulesListWidget(this);
    list->setRules(adblockList);
    lay->addWidget(list);
}

AdBlockAutomaticRulesListWidgetTest::~AdBlockAutomaticRulesListWidgetTest()
{
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("+[url]"), QStringLiteral("URL of adblock file list")));

    parser.process(app);

    QString fileName;
    if (!parser.positionalArguments().isEmpty()) {
        fileName = parser.positionalArguments().at(0);
    } else {
        fileName = QFileDialog::getOpenFileName(nullptr, QString(), QString(), QStringLiteral("Adblock File (*)"));
    }
    if (fileName.isEmpty()) {
        return 0;
    }

    AdBlockAutomaticRulesListWidgetTest *w = new AdBlockAutomaticRulesListWidgetTest(fileName);

    w->resize(800, 600);
    w->show();
    app.exec();
    delete w;
    return 0;
}
