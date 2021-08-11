/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "confirmbeforedeleting_private_export.h"
#include <QDialog>
class ConfirmBeforeDeletingMessageBoxWidget;
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingMessageBoxDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingMessageBoxDialog(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingMessageBoxDialog() override;
    void setInfo(const QString &str);

    Q_REQUIRED_RESULT bool useSameResult() const;

private:
    ConfirmBeforeDeletingMessageBoxWidget *const mConfirmBeforeDeletingWidget;
};
