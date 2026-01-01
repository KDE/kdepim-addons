/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DiffHighlighterTest : public QObject
{
    Q_OBJECT
public:
    explicit DiffHighlighterTest(QObject *parent = nullptr);
    ~DiffHighlighterTest() override = default;
private Q_SLOTS:
    void shouldGenerateDiff_data();
    void shouldGenerateDiff();
};
