/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSINTERFACE_H
#define AUTOMATICADDCONTACTSINTERFACE_H

#include <MessageComposer/PluginEditorCheckBeforeSendInterface>
#include <AkonadiCore/Collection>

class AutomaticAddContactsInterface : public MessageComposer::PluginEditorCheckBeforeSendInterface
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsInterface(QObject *parent = nullptr);
    ~AutomaticAddContactsInterface() override;

    Q_REQUIRED_RESULT bool exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params) override;

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

#endif // AUTOMATICADDCONTACTSINTERFACE_H
