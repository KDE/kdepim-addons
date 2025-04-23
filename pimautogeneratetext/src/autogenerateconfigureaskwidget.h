/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_private_export.h"
#include <QWidget>

class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureAskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskWidget(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskWidget() override;
};
