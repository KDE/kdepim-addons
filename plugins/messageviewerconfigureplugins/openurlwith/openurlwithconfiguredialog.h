/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libopenurlwithconfigure_export.h"
#include <QDialog>
class OpenUrlWithConfigureWidget;
class LIBOPENURLWITHCONFIGURE_EXPORT OpenUrlWithConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureDialog(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureDialog() override;

private:
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotAccepted();
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void readConfig();
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void writeConfig();
    OpenUrlWithConfigureWidget *const mOpenUrlWithWidget;
};
