/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class TranslatorConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureWidget() override;
};
