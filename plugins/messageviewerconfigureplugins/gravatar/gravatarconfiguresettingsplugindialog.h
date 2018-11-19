/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H
#define GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H

#include <PimCommon/ConfigurePluginDialog>

class GravatarConfigureSettingsPluginWidget;
class GravatarConfigureSettingsPluginDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginDialog(QWidget *parent = nullptr);
    ~GravatarConfigureSettingsPluginDialog() override;

    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
private:
    GravatarConfigureSettingsPluginWidget *mWidget = nullptr;
};

#endif // GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H
