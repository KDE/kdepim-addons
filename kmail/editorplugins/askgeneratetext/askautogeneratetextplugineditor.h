/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class AskAutogenerateTextPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit AskAutogenerateTextPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AskAutogenerateTextPluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent = nullptr) override;
Q_SIGNALS:
    void configChanged();
};
