/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

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
    LIBDKIMVERIFYCONFIGURE_NO_EXPORT void slotAccepted();
    LIBDKIMVERIFYCONFIGURE_NO_EXPORT void readConfig();
    LIBDKIMVERIFYCONFIGURE_NO_EXPORT void writeConfig();
    DKIMAuthenticationVerifiedServerWidget *const mAuthenticationVerifiedWidget;
};
