/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QComboBox>

class CheckFolderSizeAccountComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountComboBox(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountComboBox() override;
};
