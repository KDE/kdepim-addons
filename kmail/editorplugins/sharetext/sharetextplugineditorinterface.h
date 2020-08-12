/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SHARETEXTPLUGINEDITORINTERFACE_H
#define SHARETEXTPLUGINEDITORINTERFACE_H

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

#endif
