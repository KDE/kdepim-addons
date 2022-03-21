/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KPIMTextEdit/SelectSpecialCharDialog>
#include <MessageComposer/PluginEditorInterface>
#include <QPointer>

class InsertSpecialCharacterPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit InsertSpecialCharacterPluginEditorInterface(QObject *parent = nullptr);
    ~InsertSpecialCharacterPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void charSelected(QChar c);
    void slotActivated();
    QPointer<KPIMTextEdit::SelectSpecialCharDialog> mSelectSpecialChar;
};
