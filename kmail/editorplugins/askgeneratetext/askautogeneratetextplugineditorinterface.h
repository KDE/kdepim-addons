/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>

class AskAutogenerateTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AskAutogenerateTextPluginEditorInterface(QObject *parent = nullptr);
    ~AskAutogenerateTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
};
