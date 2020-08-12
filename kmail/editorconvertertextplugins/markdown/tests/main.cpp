/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QApplication>
#include <QStandardPaths>
#include "markdowndemowidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    MarkdownDemoWidget w;
    w.show();
    app.exec();
    return 0;
}
