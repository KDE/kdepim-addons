/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateToolPluginConfigureWidget;
class TextAutoGenerateTextToolPlugin;
}
class KAIChatAddressBookPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KAIChatAddressBookPluginWidget(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent = nullptr);
    ~KAIChatAddressBookPluginWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateToolPluginConfigureWidget *const mConfigureWidget;
};
