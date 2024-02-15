/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "quicktext_export.h"
#include <QDialog>
class QuickTextConfigureWidget;
class QUICKTEXT_EXPORT QuickTextConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QuickTextConfigureDialog(QWidget *parent = nullptr);
    ~QuickTextConfigureDialog() override;

protected:
    void closeEvent(QCloseEvent *e) override;

private:
    QUICKTEXT_NO_EXPORT void writeConfig();
    QUICKTEXT_NO_EXPORT void readConfig();
    QUICKTEXT_NO_EXPORT void slotAccepted();
    QUICKTEXT_NO_EXPORT void slotExport();
    QUICKTEXT_NO_EXPORT void slotImport();
    QuickTextConfigureWidget *const mQuickTextConfigureWidget;
};
