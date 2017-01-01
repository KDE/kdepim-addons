/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include <KAboutData>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QHBoxLayout>
#include <QApplication>
#include <QStandardPaths>
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
    KAboutData aboutData(QStringLiteral("AdBlockAutomaticRulesListWidget_gui"), i18n("AdBlockAutomaticRulesListWidget_Gui"), QStringLiteral("1.0"));
    aboutData.setShortDescription(i18n("Test for AdBlockAutomaticRulesListWidget"));
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("+[url]"), i18n("URL of adblock file list")));

    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    QString fileName;
    if (parser.positionalArguments().count()) {
        fileName = parser.positionalArguments().at(0);
    } else {
        fileName = QFileDialog::getOpenFileName(0, QString(), QString(), i18n("Adblock File (*)"));
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

