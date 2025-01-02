/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "dkimconfigure_private_export.h"
#include <QWidget>
namespace MessageViewer
{
class DKIMManagerKeyWidget;
}
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMKeyRecordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMKeyRecordWidget(QWidget *parent = nullptr);
    ~DKIMKeyRecordWidget() override;

    void loadSettings();
    void saveSettings();
    void resetSettings();

private:
    LIBDKIMVERIFYCONFIGURE_NO_EXPORT void readConfig();
    LIBDKIMVERIFYCONFIGURE_NO_EXPORT void writeConfig();
    MessageViewer::DKIMManagerKeyWidget *const mManagerKeyWidget;
};
