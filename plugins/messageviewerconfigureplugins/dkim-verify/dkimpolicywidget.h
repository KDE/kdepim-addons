/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "dkimconfigure_private_export.h"
#include <QWidget>
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMPolicyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMPolicyWidget(QWidget *parent = nullptr);
    ~DKIMPolicyWidget() override;
};
