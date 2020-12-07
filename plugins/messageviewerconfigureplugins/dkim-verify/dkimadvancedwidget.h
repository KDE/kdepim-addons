/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMADVANCEDWIDGET_H
#define DKIMADVANCEDWIDGET_H

#include <QWidget>
#include "dkimconfigure_private_export.h"
class QComboBox;
class QCheckBox;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAdvancedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMAdvancedWidget(QWidget *parent = nullptr);
    ~DKIMAdvancedWidget() override;
    void loadSettings();
    void saveSettings();
    void resetSettings();
private:
    void slotConfigureAuthenticationServer();
    QComboBox *mSha1Policy = nullptr;
    QCheckBox *mCheckDKIMWhenOnlyTesting = nullptr;
    QCheckBox *mUseAuthenticationResultRelaxedParser = nullptr;
    QComboBox *mSmallKeyPolicy = nullptr;
};

#endif // DKIMADVANCEDWIDGET_H
