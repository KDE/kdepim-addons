/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERWIDGETTEST_H
#define SELECTIMAPFOLDERWIDGETTEST_H

#include <QObject>

class SelectImapFolderWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderWidgetTest(QObject *parent = nullptr);
    ~SelectImapFolderWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // SELECTIMAPFOLDERWIDGETTEST_H
