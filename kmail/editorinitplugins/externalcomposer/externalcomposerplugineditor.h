/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInit>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class ExternalComposerPluginEditor : public MessageComposer::PluginEditorInit
{
    Q_OBJECT
public:
    explicit ExternalComposerPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ExternalComposerPluginEditor() override;

    MessageComposer::PluginEditorInitInterface *createInterface(QObject *parent = nullptr) override;

    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
};
