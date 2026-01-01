/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class AutoCorrectionPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AutoCorrectionPluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
};
