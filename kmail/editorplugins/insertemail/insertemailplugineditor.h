/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class InsertEmailPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~InsertEmailPluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
};
