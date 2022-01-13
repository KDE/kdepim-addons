/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "openurlwith_private_export.h"
#include <QWidget>

class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureCreateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureCreateWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureCreateWidget() override;
};
