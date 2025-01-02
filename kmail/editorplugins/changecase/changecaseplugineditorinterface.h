/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>

class ChangeCasePluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditorInterface(QObject *parent = nullptr);
    ~ChangeCasePluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotUpperCase();
    void slotLowerCase();
    void slotSentenceCase();
    void slotReverseCase();

    void sentenceCase();
    void upperCase();
    void lowerCase();
    void reverseCase();
    enum ChangeCaseType {
        Unknown = -1,
        UpperCase = 0,
        LowerCase,
        SentenseCase,
        ReverseCase,
    };
    ChangeCaseType mType = Unknown;
};
