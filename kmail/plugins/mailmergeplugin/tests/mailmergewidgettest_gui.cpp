/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "../widgets/mailmergewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    KAboutData aboutData(u"mailmergewidget_gui"_s, i18n("MailMergeWidgetTest_Gui"), u"1.0"_s);
    aboutData.setShortDescription(i18n("Test for mailmerge widget"));
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    auto w = new MailMerge::MailMergeWidget();
    w->resize(800, 600);
    w->show();
    app.exec();
    delete w;
    return 0;
}
