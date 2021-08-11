/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "confirmbeforedeleting_private_export.h"

class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingMessageBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingMessageBoxWidget(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingMessageBoxWidget() override;
};
