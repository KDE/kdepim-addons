/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class CheckFolderSizeAccountPluginWidget;
class CheckFolderSizeAccountPluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginDialog(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginDialog() override;

private:
    void readConfig();
    void writeConfig();
    CheckFolderSizeAccountPluginWidget *const mCheckFolderSizeAccountPluginWidget;
};
