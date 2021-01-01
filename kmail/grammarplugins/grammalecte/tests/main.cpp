/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QApplication>
#include <QStandardPaths>
#include "grammalectewidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    GrammalecteWidget w;
    w.show();
    app.exec();
    return 0;
}
