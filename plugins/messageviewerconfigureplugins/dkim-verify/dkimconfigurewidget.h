/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>

class DKIMConfigureTab;
class KConfigDialogManager;

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMConfigureWidget(QWidget *parent = nullptr);
    ~DKIMConfigureWidget() override;

    void loadSettings();
    void saveSettings();
    void resetSettings();

private:
    KConfigDialogManager *m_configDialogManager = nullptr;
    DKIMConfigureTab *const mTabWidget;
};
