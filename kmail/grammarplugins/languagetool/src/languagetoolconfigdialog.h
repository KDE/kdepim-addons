/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCONFIGDIALOG_H
#define LANGUAGETOOLCONFIGDIALOG_H
#include <QDialog>
#include "libkmaillanguagetool_export.h"
class LanguageToolConfigWidget;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LanguageToolConfigDialog(QWidget *parent = nullptr);
    ~LanguageToolConfigDialog() override;
private:
    Q_DISABLE_COPY(LanguageToolConfigDialog)
    void writeConfig();
    void readConfig();
    LanguageToolConfigWidget *mConfigWidget = nullptr;
};

#endif // LANGUAGETOOLCONFIGDIALOG_H
