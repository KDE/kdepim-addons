/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "openurlwith_private_export.h"
#include "openurlwithconfigurecreatewidget.h"
#include <QDialog>
class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureCreateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureCreateDialog(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureCreateDialog() override;

    [[nodiscard]] OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info() const;
    void setInfo(const OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo &i);

private:
    OpenUrlWithConfigureCreateWidget *const mOpenUrlWithCreateWidget;
};
