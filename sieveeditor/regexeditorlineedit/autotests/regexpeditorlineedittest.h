/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class RegexpEditorLineEditTest : public QObject
{
    Q_OBJECT
public:
    explicit RegexpEditorLineEditTest(QObject *parent = nullptr);
    ~RegexpEditorLineEditTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

