/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class RegExpEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegExpEditorWidget(QWidget *parent = nullptr);
    ~RegExpEditorWidget() override = default;
};

