/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
