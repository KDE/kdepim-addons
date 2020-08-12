/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTCONFIGUREDIALOG_H
#define QUICKTEXTCONFIGUREDIALOG_H
#include <QDialog>
#include "quicktext_export.h"
class QuickTextConfigureWidget;
class QUICKTEXT_EXPORT QuickTextConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QuickTextConfigureDialog(QWidget *parent = nullptr);
    ~QuickTextConfigureDialog();

protected:
    void closeEvent(QCloseEvent *e) override;

private:
    void writeConfig();
    void readConfig();
    void slotAccepted();
    void slotExport();
    void slotImport();
    QuickTextConfigureWidget *mQuickTextConfigureWidget = nullptr;
};

#endif // QUICKTEXTCONFIGUREDIALOG_H
