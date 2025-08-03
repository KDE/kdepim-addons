/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
#include <QPointer>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class AutoGenerateAnswersEditorDialog;
class AutoGenerateAnswersEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorInterface(QObject *parent = nullptr);
    ~AutoGenerateAnswersEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
    void setManager(TextAutoGenerateText::TextAutoGenerateManager *newManager);

private:
    void slotGenerateTextInProgress(const QString &str);
    void slotGenerateTextErrorOccured(const QString &errorStr);
    enum class AnswerType : uint8_t {
        Unknown = 0,
        SummaryText,
        QuickAnswer,
        FixTypo,
    };
    AnswerType mAnswerType = AnswerType::Unknown;
    TextAutoGenerateText::TextAutoGenerateManager *mManager = nullptr;
    QPointer<AutoGenerateAnswersEditorDialog> mAnswersEditorDialog = nullptr;
};
