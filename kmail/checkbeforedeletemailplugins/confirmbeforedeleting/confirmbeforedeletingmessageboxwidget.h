/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "confirmbeforedeleting_private_export.h"
class QLabel;
class QCheckBox;
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingMessageBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingMessageBoxWidget(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingMessageBoxWidget() override;

    void setInfo(const QString &str);
    Q_REQUIRED_RESULT bool useSameResult() const;

private:
    QLabel *const mLabelInfo;
    QCheckBox *const mUseSameResultForOtherCheck;
};
