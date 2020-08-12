/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMGENERALWIDGET_H
#define DKIMGENERALWIDGET_H

#include <QWidget>
#include "dkimconfigure_private_export.h"
class QCheckBox;
class QComboBox;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMGeneralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMGeneralWidget(QWidget *parent = nullptr);
    ~DKIMGeneralWidget();
    void loadSettings();
    void saveSettings();
    void resetSettings();
private:
    QCheckBox *mEnableDkimSupport = nullptr;
    QCheckBox *mSaveResult = nullptr;
    QComboBox *mSaveKey = nullptr;
    QCheckBox *mUseOnlyAuthenticationResult = nullptr;
};

#endif // DKIMGENERALWIDGET_H
