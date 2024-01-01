/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConfigureDialogTest(QObject *parent = nullptr);
    ~MarkdownConfigureDialogTest() override = default;
};
