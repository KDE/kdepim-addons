/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

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
    void slotAccepted();
    void readConfig();
    void writeConfig();
    OpenUrlWithConfigureWidget *const mOpenUrlWithWidget;
};
