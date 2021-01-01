/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGURETAB_H
#define DKIMCONFIGURETAB_H

#include <QWidget>
#include "dkimconfigure_private_export.h"

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
    DKIMGeneralWidget *mGeneralWidget = nullptr;
    DKIMKeyRecordWidget *mRecordWidget = nullptr;
    DKIMAdvancedWidget *mAdvancedWidget = nullptr;
    DKIMPolicyWidget *mPolicyWidget = nullptr;
    QTabWidget *const mTabWidget;
};

#endif // DKIMCONFIGURETAB_H
