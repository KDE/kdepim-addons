/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <MessageComposer/PluginEditorCheckBeforeSendInterface>

class AutomaticAddContactsInterface : public MessageComposer::PluginEditorCheckBeforeSendInterface
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsInterface(QObject *parent = nullptr);
    ~AutomaticAddContactsInterface() override;

    [[nodiscard]] bool exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params) override;

public Q_SLOTS:
    void reloadConfig() override;

private:
    struct AutomaticAddContactsSettings {
        AutomaticAddContactsSettings()
            : mContactCollection(Akonadi::Collection(-1))
        {
        }

        bool mEnabled = false;
        Akonadi::Collection mContactCollection;
    };
    QHash<uint, AutomaticAddContactsSettings> mHashSettings;
};
