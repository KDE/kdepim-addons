/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class InsertShorturlPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~InsertShorturlPluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;

    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent = nullptr) override;
Q_SIGNALS:
    void configChanged();
};
