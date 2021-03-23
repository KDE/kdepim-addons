/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/ConfigurePluginDialog>

class AutomaticAddContactsConfigureWidget;
class AutomaticAddContactsConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsConfigureDialog(QWidget *parent = nullptr);
    ~AutomaticAddContactsConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    AutomaticAddContactsConfigureWidget *mConfigureWidget = nullptr;
};

