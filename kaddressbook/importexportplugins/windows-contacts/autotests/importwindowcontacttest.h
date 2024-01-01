/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ImportWindowContactTest : public QObject
{
    Q_OBJECT
public:
    explicit ImportWindowContactTest(QObject *parent = nullptr);
    ~ImportWindowContactTest() override = default;
private Q_SLOTS:
    void shouldImportWindowContact_data();
    void shouldImportWindowContact();
};
