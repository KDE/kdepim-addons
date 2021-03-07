/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERMODELTEST_H
#define SELECTIMAPFOLDERMODELTEST_H

#include <QObject>

class SelectImapFolderModelTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderModelTest(QObject *parent = nullptr);
    ~SelectImapFolderModelTest() override;

private Q_SLOTS:
    void shouldNotCreateModelIfAccountIsNotValid();
};

#endif // SELECTIMAPFOLDERMODELTEST_H
