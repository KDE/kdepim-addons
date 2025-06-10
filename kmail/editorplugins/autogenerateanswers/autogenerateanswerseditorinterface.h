/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
class AutoGenerateAnswersEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorInterface(QObject *parent = nullptr);
    ~AutoGenerateAnswersEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotGenerateTextInProgress(const QString &str);
    enum class AnswerType : uint8_t {
        Unknown = 0,
        SummaryText,
        QuickAnswer,
        FixTypo,
    };
    AnswerType mAnswerType = AnswerType::Unknown;
};
