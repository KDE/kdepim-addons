/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> askInfos() const;
    void setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void readConfig();
    PIMAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    AutogenerateConfigureAskWidget *const mAutogenerateConfigureAskWidget;
};
