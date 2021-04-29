/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSendConfigureWidget>
class QWidget;
class ConfirmAddressConfigureTab;
class ConfirmAddressConfigureWidget : public MessageComposer::PluginEditorCheckBeforeSendConfigureWidget
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
    ConfirmAddressConfigureTab *mConfirmAddressConfigureTab = nullptr;
};

