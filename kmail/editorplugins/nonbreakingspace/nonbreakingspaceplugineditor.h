/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class NonBreakingSpacePluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit NonBreakingSpacePluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~NonBreakingSpacePluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
};
