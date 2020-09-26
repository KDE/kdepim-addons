/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSPAGEBASE_H
#define FOLDERCONFIGURESETTINGSPAGEBASE_H

#include <QWidget>

class FolderConfigureSettingsPageBase : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPageBase(QWidget *parent = nullptr);
    ~FolderConfigureSettingsPageBase();
};

#endif // FOLDERCONFIGURESETTINGSPAGEBASE_H
