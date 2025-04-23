/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_export.h"
#include <QDialog>

class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskDialog(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskDialog() override;
};
