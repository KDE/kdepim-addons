/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>
class QCheckBox;
class QPushButton;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMPolicyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMPolicyWidget(QWidget *parent = nullptr);
    ~DKIMPolicyWidget() override;
    void loadSettings();
    void saveSettings();
    void resetSettings();

private:
    QCheckBox *const mVerifyIfEmailMustBeSigned;
    QCheckBox *const mUseDMARC;
    QCheckBox *const mUseDefaultRules;
    QCheckBox *const mAutoGenerateRule;
    QCheckBox *const mReadAuthResultHeader;
    QCheckBox *const mAutoGenerateOnlyIfSenderInSDID;
    QPushButton *const mRulesButton;
};

