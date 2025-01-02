/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConvertText>

class MarkdownPlugin : public MessageComposer::PluginEditorConvertText
{
    Q_OBJECT
public:
    explicit MarkdownPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~MarkdownPlugin() override;

    MessageComposer::PluginEditorConvertTextInterface *createInterface(QObject *parent) override;

    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
    [[nodiscard]] QString description() const override;
    [[nodiscard]] bool canWorkOnHtml() const override;
    [[nodiscard]] bool hasStatusBarSupport() const override;

    [[nodiscard]] bool hasPopupMenuSupport() const override;
    [[nodiscard]] bool hasToolBarSupport() const override;
};
