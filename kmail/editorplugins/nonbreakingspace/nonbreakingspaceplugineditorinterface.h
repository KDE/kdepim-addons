/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>

class NonBreakingSpacePluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit NonBreakingSpacePluginEditorInterface(QObject *parent = nullptr);
    ~NonBreakingSpacePluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private Q_SLOTS:
    void slotActivated();
};
