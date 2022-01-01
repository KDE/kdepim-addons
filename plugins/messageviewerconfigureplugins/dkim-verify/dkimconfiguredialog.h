/*
   SPDX-FileCopyrightText: 2018-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libdkimverifyconfigure_export.h"
#include <QDialog>

class DKIMConfigureWidget;
class LIBDKIMVERIFYCONFIGURE_EXPORT DKIMConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DKIMConfigureDialog(QWidget *parent = nullptr);
    ~DKIMConfigureDialog() override;

private:
    void slotReset();
    void readConfig();
    void slotAccepted();
    void writeConfig();
    DKIMConfigureWidget *const mConfigureWidget;
};
