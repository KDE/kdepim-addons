/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammarResultUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultUtilTest(QObject *parent = nullptr);
    ~GrammarResultUtilTest() override = default;
private Q_SLOTS:
    void shouldReplaceWord();
};
