/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
class CheckFolderSizeAccountPluginConfigureWidget;
class CheckFolderSizeAccountPluginConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginConfigureDialog(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginConfigureDialog() override;

private:
    void slotAccept();
    CheckFolderSizeAccountPluginConfigureWidget *const mCheckFolderSizeAccountPluginConfigureWidget;
};
