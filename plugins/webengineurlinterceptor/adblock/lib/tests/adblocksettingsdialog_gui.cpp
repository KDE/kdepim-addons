/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCommandLineParser>
#include <QDialogButtonBox>
#include <QStandardPaths>
#include "../widgets/adblocksettingwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto *w = new AdBlock::AdBlockSettingWidget;
    QDialog dlg;
    auto *layout = new QVBoxLayout;
    dlg.setLayout(layout);
    layout->addWidget(w);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    layout->addWidget(buttonBox);

    w->doLoadFromGlobalSettings();
    if (dlg.exec()) {
        w->save();
    }
    return 0;
}
