/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef CHECKBEFORESENDINTERFACE_H
#define CHECKBEFORESENDINTERFACE_H

#include <MessageComposer/PluginEditorCheckBeforeSendInterface>
#include <AkonadiCore/Collection>

class AutomaticAddContactsInterface : public MessageComposer::PluginEditorCheckBeforeSendInterface
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsInterface(QObject *parent = Q_NULLPTR);
    ~AutomaticAddContactsInterface();

    bool exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params) Q_DECL_OVERRIDE;

public Q_SLOTS:
    void reloadConfig() Q_DECL_OVERRIDE;
private:
    struct AutomaticAddContactsSettings {
        AutomaticAddContactsSettings()
            : mEnabled(false),
              mContactCollection(Akonadi::Collection(-1))
        {

        }

        bool mEnabled;
        Akonadi::Collection mContactCollection;
    };
    QHash<uint, AutomaticAddContactsSettings> mHashSettings;
};

#endif // CHECKBEFORESENDINTERFACE_H
