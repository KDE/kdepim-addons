/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QDialog>
class DKIMAuthenticationVerifiedServerWidget;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerDialog(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerDialog() override;

private:
    void slotAccepted();
    void readConfig();
    void writeConfig();
    DKIMAuthenticationVerifiedServerWidget *const mAuthenticationVerifiedWidget;
};
