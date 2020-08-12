/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURETREEWIDGET_H
#define FOLDERCONFIGURETREEWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureTreeWidget(QWidget *parent = nullptr);
    ~FolderConfigureTreeWidget();
};

#endif // FOLDERCONFIGURETREEWIDGET_H
