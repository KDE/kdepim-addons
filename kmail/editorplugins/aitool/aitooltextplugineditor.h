/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class AIToolTextPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit AIToolTextPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AIToolTextPluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
    [[nodiscard]] bool hasConfigureDialog() const override;
};
