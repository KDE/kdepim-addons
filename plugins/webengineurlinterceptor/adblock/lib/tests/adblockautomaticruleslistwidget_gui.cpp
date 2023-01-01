/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockautomaticruleslistwidget_gui.h"
#include "../widgets/adblockautomaticruleslistwidget.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVBoxLayout>
AdBlockAutomaticRulesListWidgetTest::AdBlockAutomaticRulesListWidgetTest(const QString &fileName, QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QVBoxLayout(this);
    QFile localFile(fileName);
    QString adblockList;
    if (localFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        adblockList = QString::fromLatin1(localFile.readAll());
    }
    auto list = new AdBlock::AdBlockAutomaticRulesListWidget(this);
    list->setRules(adblockList);
    lay->addWidget(list);
}

AdBlockAutomaticRulesListWidgetTest::~AdBlockAutomaticRulesListWidgetTest() = default;

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

    auto w = new AdBlockAutomaticRulesListWidgetTest(fileName);

    w->resize(800, 600);
    w->show();
    app.exec();
    delete w;
    return 0;
}
