/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class AkonadiDatabaseToolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsWidget(QWidget *parent = nullptr);
    ~AkonadiDatabaseToolsWidget() override;

    void appendText(const QString &text);
};
