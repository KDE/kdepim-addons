/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "adblockblockableelementgui.h"
#include "../lib/widgets/adblockblockableitemsdialog.h"
#include "../lib/adblockblockableitemsjob.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebEngineView>
#include <QStandardPaths>
#include <QCommandLineParser>
#include <QApplication>
using namespace AdBlock;
AdblockBlockableElementGui::AdblockBlockableElementGui(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    mWebEngineView = new QWebEngineView(this);
    mWebEngineView->load(QUrl(QStringLiteral("http://www.kde.org")));
    vbox->addWidget(mWebEngineView);
    QPushButton *button = new QPushButton(QStringLiteral("search adblock"), this);
    connect(button, &QPushButton::clicked, this, &AdblockBlockableElementGui::slotSearchAdblock);
    vbox->addWidget(button);
}

AdblockBlockableElementGui::~AdblockBlockableElementGui()
{

}

void AdblockBlockableElementGui::slotSearchItemsDone(const QVector<AdBlock::AdBlockResult> &result)
{
    AdBlockBlockableItemsDialog dlg(this);
    dlg.setAdblockResult(result);
    dlg.exec();
}

void AdblockBlockableElementGui::slotSearchAdblock()
{
    AdBlockBlockableItemsJob *job = new AdBlockBlockableItemsJob(this);
    job->setWebEngineView(mWebEngineView);
    connect(job, &AdBlockBlockableItemsJob::searchItemsDone, this, &AdblockBlockableElementGui::slotSearchItemsDone);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    AdblockBlockableElementGui *dialog = new AdblockBlockableElementGui;
    dialog->resize(800, 600);
    dialog->show();
    app.exec();
    delete dialog;
    return 0;
}

