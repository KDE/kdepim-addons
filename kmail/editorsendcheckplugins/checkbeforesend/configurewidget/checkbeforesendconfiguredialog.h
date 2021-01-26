/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKBEFORESENDCONFIGUREDIALOG_H
#define CHECKBEFORESENDCONFIGUREDIALOG_H

#include <PimCommon/ConfigurePluginDialog>
class CheckBeforeSendConfigureWidget;
class CheckBeforeSendConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureDialog(QWidget *parent = nullptr);
    ~CheckBeforeSendConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    CheckBeforeSendConfigureWidget *mConfigureWidget = nullptr;
};

#endif // CHECKBEFORESENDCONFIGUREDIALOG_H
