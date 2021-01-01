/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCONFIGUREDIALOG_H
#define CONFIRMADDRESSCONFIGUREDIALOG_H

#include <PimCommon/ConfigurePluginDialog>
class ConfirmAddressConfigureWidget;
class ConfirmAddressConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureDialog(QWidget *parent = nullptr);
    ~ConfirmAddressConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;
private:
    ConfirmAddressConfigureWidget *mConfigureWidget = nullptr;
};

#endif // CONFIRMADDRESSCONFIGUREDIALOG_H
