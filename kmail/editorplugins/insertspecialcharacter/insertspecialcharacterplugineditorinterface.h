/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
#include <QPointer>
#include <TextAddonsWidgets/SelectSpecialCharDialog>

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
    QPointer<TextAddonsWidgets::SelectSpecialCharDialog> mSelectSpecialChar;
};
