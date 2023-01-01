/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>

class ShareTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorInterface(QObject *parent = nullptr);
    ~ShareTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
};
