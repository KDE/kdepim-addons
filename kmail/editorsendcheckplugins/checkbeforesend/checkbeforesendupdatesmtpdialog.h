/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] bool changeSmtp() const;

private:
    QCheckBox *const mChangeSmtp;
};
