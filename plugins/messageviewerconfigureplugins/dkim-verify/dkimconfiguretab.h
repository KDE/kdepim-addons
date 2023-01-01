/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>

class QTabWidget;
class DKIMGeneralWidget;
class DKIMKeyRecordWidget;
class DKIMAdvancedWidget;
class DKIMPolicyWidget;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMConfigureTab : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMConfigureTab(QWidget *parent = nullptr);
    ~DKIMConfigureTab() override;

    void loadSettings();
    void saveSettings();
    void resetSettings();

private:
    void initTab();
    DKIMGeneralWidget *const mGeneralWidget;
    DKIMKeyRecordWidget *const mRecordWidget;
    DKIMAdvancedWidget *const mAdvancedWidget;
    DKIMPolicyWidget *const mPolicyWidget;
    QTabWidget *const mTabWidget;
};
