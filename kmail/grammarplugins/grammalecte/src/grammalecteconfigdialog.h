/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTECONFIGDIALOG_H
#define GRAMMALECTECONFIGDIALOG_H
#include "libkmailgrammalecte_export.h"
#include <QDialog>
class GrammalecteConfigWidget;
class LIBKMAILGRAMMALECTE_EXPORT GrammalecteConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GrammalecteConfigDialog(QWidget *parent = nullptr, bool disableMessageBox = false);
    ~GrammalecteConfigDialog() override;

private:
    Q_DISABLE_COPY(GrammalecteConfigDialog)
    void writeConfig();
    void readConfig();
    GrammalecteConfigWidget *mConfigWidget = nullptr;
};

#endif // GRAMMALECTECONFIGDIALOG_H
