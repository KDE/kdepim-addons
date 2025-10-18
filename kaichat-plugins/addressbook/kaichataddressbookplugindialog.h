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
class CurrentDateTimeToolPluginWidget;
class KAIChatAddressBookPluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KAIChatAddressBookPluginDialog(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent = nullptr);
    ~KAIChatAddressBookPluginDialog() override;

private:
    CurrentDateTimeToolPluginWidget *const mCurrentDateTimeToolPluginWidget;
};
