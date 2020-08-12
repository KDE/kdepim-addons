/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOCORRECTIONPLUGINEDITORINTERFACE_H
#define AUTOCORRECTIONPLUGINEDITORINTERFACE_H

#include <MessageComposer/PluginEditorInterface>

class AutoCorrectionPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditorInterface(QObject *parent = nullptr);
    ~AutoCorrectionPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotAutoCorrectAllText();
    void slotAutoCorrectSelectedText();
    bool mSelectedText = false;
};

#endif
