/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>
class QCheckBox;
class QComboBox;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMGeneralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMGeneralWidget(QWidget *parent = nullptr);
    ~DKIMGeneralWidget() override;
    void saveSettings();

private:
    QCheckBox *const mEnableDkimSupport;
    QCheckBox *const mSaveResult;
    QComboBox *const mSaveKey;
    QCheckBox *const mUseOnlyAuthenticationResult;
};
