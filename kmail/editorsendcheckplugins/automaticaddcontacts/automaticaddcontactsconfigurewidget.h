/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConfigureBaseWidget>
class QWidget;
class AutomaticAddContactsConfigureTab;
class AutomaticAddContactsConfigureWidget : public MessageComposer::PluginEditorConfigureBaseWidget
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsConfigureWidget(QWidget *parent = nullptr);
    ~AutomaticAddContactsConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    AutomaticAddContactsConfigureTab *const mConfigureTab;
};
