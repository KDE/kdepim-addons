/*
   SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class QCheckBox;
class CheckBeforeSendUpdateSmtpDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckBeforeSendUpdateSmtpDialog(QWidget *parent = nullptr);
    ~CheckBeforeSendUpdateSmtpDialog() override;

    Q_REQUIRED_RESULT bool changeSmtp() const;

private:
    QCheckBox *const mChangeSmtp;
};

