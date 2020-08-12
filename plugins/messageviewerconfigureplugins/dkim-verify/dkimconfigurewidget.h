/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREWIDGET_H
#define DKIMCONFIGUREWIDGET_H

#include <QWidget>
#include "dkimconfigure_private_export.h"

class DKIMConfigureTab;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMConfigureWidget(QWidget *parent = nullptr);
    ~DKIMConfigureWidget();

    void loadSettings();
    void saveSettings();
    void resetSettings();
private:
    DKIMConfigureTab *mTabWidget = nullptr;
};

#endif // DKIMCONFIGUREWIDGET_H
