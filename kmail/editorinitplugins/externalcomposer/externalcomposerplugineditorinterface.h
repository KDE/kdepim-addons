/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXTERNALCOMPOSERPLUGINEDITORINTERFACE_H
#define EXTERNALCOMPOSERPLUGINEDITORINTERFACE_H

#include <MessageComposer/PluginEditorInitInterface>

class ExternalComposerPluginEditorInterface : public MessageComposer::PluginEditorInitInterface
{
    Q_OBJECT
public:
    explicit ExternalComposerPluginEditorInterface(QObject *parent = nullptr);
    ~ExternalComposerPluginEditorInterface() override;
    Q_REQUIRED_RESULT bool exec() override;

    void reloadConfig() override;
private:
    QString mExternalComposerPath;
    bool mEnabled = false;
};

#endif
