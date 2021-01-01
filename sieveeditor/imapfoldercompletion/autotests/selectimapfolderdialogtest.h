/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERDIALOGTEST_H
#define SELECTIMAPFOLDERDIALOGTEST_H

#include <QObject>

class SelectImapFolderDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderDialogTest(QObject *parent = nullptr);
    ~SelectImapFolderDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // SELECTIMAPFOLDERDIALOGTEST_H
