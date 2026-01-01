/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConfigureBaseWidget>
class QWidget;
class ConfirmAddressConfigureTab;
class ConfirmAddressConfigureWidget : public MessageComposer::PluginEditorConfigureBaseWidget
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureWidget(QWidget *parent = nullptr);
    ~ConfirmAddressConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    void slotEnableChanged(bool state);
    ConfirmAddressConfigureTab *const mConfirmAddressConfigureTab;
};
