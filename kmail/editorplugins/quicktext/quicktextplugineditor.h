/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class QuickTextPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit QuickTextPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~QuickTextPluginEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasStatusBarSupport() const override;

    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;

    [[nodiscard]] bool canProcessKeyEvent() const override;
};
