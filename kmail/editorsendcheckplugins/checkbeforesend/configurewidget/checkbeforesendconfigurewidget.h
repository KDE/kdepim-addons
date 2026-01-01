/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConfigureBaseWidget>
class QWidget;

class QCheckBox;
class CheckBeforeSendConfigureWidget : public MessageComposer::PluginEditorConfigureBaseWidget
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureWidget(QWidget *parent = nullptr);
    ~CheckBeforeSendConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *const mCheckPlainTextMail;
    QCheckBox *const mCheckMailTransport;
    QCheckBox *const mCheckDuplicateEmailsAddresses;
    QCheckBox *const mCheckSendAttachments;
};
