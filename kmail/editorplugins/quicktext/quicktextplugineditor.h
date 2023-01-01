/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

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

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasStatusBarSupport() const override;

    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;

    Q_REQUIRED_RESULT bool canProcessKeyEvent() const override;
};
