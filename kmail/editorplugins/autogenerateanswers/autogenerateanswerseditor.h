/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
}
class AutoGenerateAnswersEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AutoGenerateAnswersEditor() override;

    [[nodiscard]] MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
    [[nodiscard]] bool hasConfigureDialog() const override;

private:
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
