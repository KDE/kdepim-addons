/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "openurlwith_private_export.h"
#include <QWidget>
class QTreeWidget;
class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureWidget() override;
    void loadSettings();
    void writeSettings();

private:
    QTreeWidget *const mTreeWidget;
};
