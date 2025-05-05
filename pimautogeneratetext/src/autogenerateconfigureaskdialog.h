/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autogenerateconfigureaskinfo.h"
#include "pimautogeneratetext_export.h"
#include <QDialog>
class AutogenerateConfigureAskWidget;
class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskDialog(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskDialog() override;

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> askItems() const;
    void setAskItems(const QList<AutogenerateConfigureAskInfo> &newAskItems);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void readConfig();
    PIMAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    AutogenerateConfigureAskWidget *const mAutogenerateConfigureAskWidget;
};
