/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSendInterface>
class CheckBeforeSendInterface : public MessageComposer::PluginEditorCheckBeforeSendInterface
{
    Q_OBJECT
public:
    explicit CheckBeforeSendInterface(QObject *parent = nullptr);
    ~CheckBeforeSendInterface() override;

    [[nodiscard]] bool exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params) override;

public Q_SLOTS:
    void reloadConfig() override;

private:
    bool mSendPlainText = false;
    bool mCheckMailTransport = false;
    bool mCheckDuplicateEmails = false;
    bool mCheckSendAttachments = false;
};
