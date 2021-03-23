/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSendConfigureWidget>
#include <QWidget>

class QCheckBox;
class CheckBeforeSendConfigureWidget : public MessageComposer::PluginEditorCheckBeforeSendConfigureWidget
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureWidget(QWidget *parent = nullptr);
    ~CheckBeforeSendConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *mCheckPlainTextMail = nullptr;
    QCheckBox *mCheckMailTransport = nullptr;
    QCheckBox *mCheckDuplicateEmailsAddresses = nullptr;
    QCheckBox *mCheckSendAttachments = nullptr;
};

