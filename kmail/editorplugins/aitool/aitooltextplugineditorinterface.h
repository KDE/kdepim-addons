/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
class AIToolTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AIToolTextPluginEditorInterface(QObject *parent = nullptr);
    ~AIToolTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotActivated();
};
