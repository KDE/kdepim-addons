/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <PimCommon/SimpleStringListEditor>
#include <QWidget>

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerSelectorWidget : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerSelectorWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerSelectorWidget() override;
};

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerWidget() override;
    void loadSettings();
    void saveSettings();

private:
    DKIMAuthenticationVerifiedServerSelectorWidget *const mSelector;
};
