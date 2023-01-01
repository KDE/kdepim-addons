/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/ConfigurePluginDialog>
class CheckBeforeSendConfigureWidget;
class CheckBeforeSendConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureDialog(QWidget *parent = nullptr);
    ~CheckBeforeSendConfigureDialog() override;

protected:
    Q_REQUIRED_RESULT QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    CheckBeforeSendConfigureWidget *mConfigureWidget = nullptr;
};
