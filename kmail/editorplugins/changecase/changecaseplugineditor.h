/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class ChangeCasePluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ChangeCasePluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
};
