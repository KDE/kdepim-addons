/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPlugin;
}
class KAIChatAddressBookPluginWidget;
class KAIChatCalendarPluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KAIChatCalendarPluginDialog(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent = nullptr);
    ~KAIChatCalendarPluginDialog() override;

private:
    KAIChatAddressBookPluginWidget *const mAddressbookToolPluginWidget;
};
