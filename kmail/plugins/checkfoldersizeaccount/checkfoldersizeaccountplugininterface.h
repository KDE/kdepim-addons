/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QPointer>

class CheckFolderSizeAccountPluginDialog;
class CheckFolderSizeAccountPluginInterface : public PimCommon::GenericPluginInterface
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginInterface(QObject *parent = nullptr);
    ~CheckFolderSizeAccountPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
    QPointer<CheckFolderSizeAccountPluginDialog> mCheckFolderSizeDialog;
};
