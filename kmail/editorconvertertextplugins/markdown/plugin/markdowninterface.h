/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConvertTextInterface>
class QObject;
#include <QPointer>

namespace MessageComposer
{
class StatusBarLabelToggledState;
}

class KActionCollection;
class MarkdownPreviewDialog;
class MarkdownInterface : public MessageComposer::PluginEditorConvertTextInterface
{
    Q_OBJECT
public:
    explicit MarkdownInterface(QObject *parent = nullptr);
    ~MarkdownInterface() override;
    void createAction(KActionCollection *ac) override;

    [[nodiscard]] bool reformatText() override;
    [[nodiscard]] MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus convertTextToFormat(MessageComposer::TextPart *textPart) override;
    void enableDisablePluginActions(bool richText) override;

public Q_SLOTS:
    void reloadConfig() override;

private:
    void addEmbeddedImages(MessageComposer::TextPart *textPart, QString &textVersion, QString &htmlVersion) const;
    void addBold();
    void addItalic();
    void addTitle(int i);
    void addLink();
    void addImage();
    void addHorizontalRule();
    void slotActivated(bool checked);
    void slotSelectionChanged();
    void addCode();
    void addBlockQuote();
    QAction *mAction = nullptr;
    QAction *mBoldAction = nullptr;
    QAction *mItalicAction = nullptr;
    QAction *mCodeAction = nullptr;
    QAction *mBlockQuoteAction = nullptr;
    QAction *mPopupMenuAction = nullptr;
    QPointer<MarkdownPreviewDialog> mDialog;
    bool mEnableEmbeddedLabel = false;
    bool mEnableExtraDefinitionLists = false;
    MessageComposer::StatusBarLabelToggledState *mStatusBarLabel = nullptr;
};
