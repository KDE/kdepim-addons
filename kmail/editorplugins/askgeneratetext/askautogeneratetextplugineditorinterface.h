/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
class AutogenerateConfigureAskManager;
class AskAutogenerateTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AskAutogenerateTextPluginEditorInterface(QObject *parent = nullptr);
    ~AskAutogenerateTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    void slotRefreshMenu();

Q_SIGNALS:
    void refreshMenu();

private:
    void slotAskRequested(const QString &msg);
    AutogenerateConfigureAskManager *const mAskManager;
    QString mAskMsg;
};
