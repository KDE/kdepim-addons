/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "confirmbeforedeleting_private_export.h"
#include <QDialog>
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingMessageBox(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingMessageBox() override;
};
