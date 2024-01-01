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
    void writeConfig();
    void readConfig();
    void slotAccepted();
    void slotExport();
    void slotImport();
    QuickTextConfigureWidget *const mQuickTextConfigureWidget;
};
