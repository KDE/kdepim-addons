/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
    Q_REQUIRED_RESULT QString description() const override;
    Q_REQUIRED_RESULT bool canWorkOnHtml() const override;
    Q_REQUIRED_RESULT bool hasStatusBarSupport() const override;

    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
    Q_REQUIRED_RESULT bool hasToolBarSupport() const override;
};
