/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateToolPluginConfigureWidget;
class TextAutoGenerateTextToolPlugin;
}
class KAIChatCalendarPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KAIChatCalendarPluginWidget(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent = nullptr);
    ~KAIChatCalendarPluginWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateToolPluginConfigureWidget *const mConfigureWidget;
};
