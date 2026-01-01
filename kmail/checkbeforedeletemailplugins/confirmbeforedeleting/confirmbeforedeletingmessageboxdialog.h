/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "kmailconfirmbeforedeleting_export.h"
#include <QDialog>
class ConfirmBeforeDeletingMessageBoxWidget;
class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingMessageBoxDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingMessageBoxDialog(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingMessageBoxDialog() override;
    void setInfo(const QString &str);

    [[nodiscard]] bool useSameResult() const;

private:
    ConfirmBeforeDeletingMessageBoxWidget *const mConfirmBeforeDeletingWidget;
};
