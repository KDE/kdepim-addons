/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autogenerateconfigureaskitem.h"
#include "pimautogeneratetext_export.h"
#include <QDialog>
class AutogenerateConfigureAskWidget;
class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskDialog(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskDialog() override;

    [[nodiscard]] QList<AutogenerateConfigureAskItem> askItems() const;
    void setAskItems(const QList<AutogenerateConfigureAskItem> &newAskItems);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void readConfig();
    PIMAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    AutogenerateConfigureAskWidget *const mAutogenerateConfigureAskWidget;
};
