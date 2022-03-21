/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libkmaillanguagetool_export.h"
#include <QDialog>
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
    LanguageToolConfigWidget *const mConfigWidget;
};
