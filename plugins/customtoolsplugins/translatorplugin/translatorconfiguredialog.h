/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

class TranslatorConfigureDialog : public QDialog
{
public:
    explicit TranslatorConfigureDialog(QWidget *parent = nullptr);
    ~TranslatorConfigureDialog() override;
};
