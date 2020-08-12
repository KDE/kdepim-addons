/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H
#define DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H

#include <QWidget>
#include "dkimconfigure_private_export.h"
#include <PimCommon/SimpleStringListEditor>

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerSelectorWidget : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerSelectorWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerSelectorWidget();
};

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerWidget();
    void loadSettings();
    void saveSettings();
private:
    DKIMAuthenticationVerifiedServerSelectorWidget *mSelector = nullptr;
};

#endif // DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H
