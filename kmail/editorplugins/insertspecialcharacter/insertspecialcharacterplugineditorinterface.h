/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INSERTSPECIALCHARACTERPLUGINEDITORINTERFACE_H
#define INSERTSPECIALCHARACTERPLUGINEDITORINTERFACE_H

#include <MessageComposer/PluginEditorInterface>
#include <KPIMTextEdit/SelectSpecialCharDialog>
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

#endif
