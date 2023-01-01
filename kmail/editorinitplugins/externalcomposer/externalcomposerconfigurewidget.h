/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorConfigureBaseWidget>
class QWidget;
class QCheckBox;
class KUrlRequester;
class ExternalComposerConfigureWidget : public MessageComposer::PluginEditorConfigureBaseWidget
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureWidget(QWidget *parent = nullptr);
    ~ExternalComposerConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *const mExternalEditorCheck;
    KUrlRequester *const mEditorRequester;
};
