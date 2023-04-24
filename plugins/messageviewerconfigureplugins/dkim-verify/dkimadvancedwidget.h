/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>
class QComboBox;
class QCheckBox;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAdvancedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMAdvancedWidget(QWidget *parent = nullptr);
    ~DKIMAdvancedWidget() override;

private:
    void slotConfigureAuthenticationServer();
    QComboBox *const mSha1Policy;
    QCheckBox *const mCheckDKIMWhenOnlyTesting;
    QCheckBox *const mUseAuthenticationResultRelaxedParser;
    QComboBox *const mSmallKeyPolicy;
};
