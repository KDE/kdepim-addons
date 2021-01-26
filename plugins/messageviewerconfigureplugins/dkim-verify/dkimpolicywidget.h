/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMPOLICYWIDGET_H
#define DKIMPOLICYWIDGET_H

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
    QCheckBox *mVerifyIfEmailMustBeSigned = nullptr;
    QCheckBox *mUseDMARC = nullptr;
    QCheckBox *mUseDefaultRules = nullptr;
    QCheckBox *mAutoGenerateRule = nullptr;
    QCheckBox *mReadAuthResultHeader = nullptr;
    QCheckBox *mAutoGenerateOnlyIfSenderInSDID = nullptr;
    QPushButton *mRulesButton = nullptr;
};

#endif // DKIMPOLICYWIDGET_H
