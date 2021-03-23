/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/ConfigurePluginDialog>

class ExternalComposerConfigureWidget;
class ExternalComposerConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureDialog(QWidget *parent = nullptr);
    ~ExternalComposerConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    ExternalComposerConfigureWidget *mConfigureWidget = nullptr;
};

