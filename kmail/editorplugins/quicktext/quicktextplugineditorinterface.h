/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MailCommon/SnippetsModel>
#include <MessageComposer/PluginEditorInterface>
#include <QTextCursor>
class QuickTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit QuickTextPluginEditorInterface(QObject *parent = nullptr);
    ~QuickTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    [[nodiscard]] bool processProcessKeyEvent(QKeyEvent *event) override;

    void reloadConfig();

private:
    void updateSnippetsInfo();
    void slotActivated();
    void selectPreviousWord(QTextCursor &cursor, int cursorPosition);
    QList<MailCommon::SnippetsInfo> mSnippetsInfo;
    MailCommon::SnippetsModel *const mModel;
};
