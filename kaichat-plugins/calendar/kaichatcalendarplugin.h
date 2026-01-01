/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QVariant>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
class KAIChatCalendarPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
    Q_OBJECT
public:
    explicit KAIChatCalendarPlugin(QObject *parent = nullptr, const QVariantList & = {});
    ~KAIChatCalendarPlugin() override;

    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    void showConfigureDialog(QWidget *parent) override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *callTool() override;

    [[nodiscard]] int order() const override;
    [[nodiscard]] QString iconName() const override;
};
