/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QVariant>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
class KAIChatAddressBookPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
    Q_OBJECT
public:
    explicit KAIChatAddressBookPlugin(QObject *parent = nullptr, const QVariantList & = {});
    ~KAIChatAddressBookPlugin() override;

    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    void showConfigureDialog(QWidget *parent) override;

    void
    callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info) override;
};
