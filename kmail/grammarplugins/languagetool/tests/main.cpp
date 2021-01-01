/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QApplication>
#include <QStandardPaths>
#include "languagetoolwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    LanguageToolWidget w;
    w.show();
    app.exec();
    return 0;
}
