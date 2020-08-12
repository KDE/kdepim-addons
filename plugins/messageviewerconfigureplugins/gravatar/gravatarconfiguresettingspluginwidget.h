/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARCONFIGURESETTINGSPLUGINWIDGET_H
#define GRAVATARCONFIGURESETTINGSPLUGINWIDGET_H

#include <MessageViewer/MessageViewerConfigureSettingsPluginWidget>
class QCheckBox;
namespace Gravatar {
class GravatarConfigureSettingsWidget;
}
class GravatarConfigureSettingsPluginWidget : public MessageViewer::MessageViewerConfigureSettingsPluginWidget
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginWidget(QWidget *parent = nullptr);
    ~GravatarConfigureSettingsPluginWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    Gravatar::GravatarConfigureSettingsWidget *mGravatarConfigWidget = nullptr;
    QCheckBox *mEnableGravatarSupport = nullptr;
};

#endif // GRAVATARCONFIGURESETTINGSPLUGINWIDGET_H
