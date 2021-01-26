/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREWIDGET_H
#define DKIMCONFIGUREWIDGET_H

#include "dkimconfigure_private_export.h"
#include <QWidget>

class DKIMConfigureTab;
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
    DKIMConfigureTab *const mTabWidget;
};

#endif // DKIMCONFIGUREWIDGET_H
