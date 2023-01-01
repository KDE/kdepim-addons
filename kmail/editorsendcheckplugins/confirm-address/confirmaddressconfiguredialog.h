/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/ConfigurePluginDialog>
class ConfirmAddressConfigureWidget;
class ConfirmAddressConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureDialog(QWidget *parent = nullptr);
    ~ConfirmAddressConfigureDialog() override;

protected:
    Q_REQUIRED_RESULT QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    ConfirmAddressConfigureWidget *mConfigureWidget = nullptr;
};
