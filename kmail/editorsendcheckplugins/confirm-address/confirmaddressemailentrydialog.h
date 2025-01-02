/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class QLineEdit;

class ConfirmAddressEmailEntryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmAddressEmailEntryDialog(QWidget *parent = nullptr);
    ~ConfirmAddressEmailEntryDialog() override = default;

    [[nodiscard]] QString emails() const;
    void setValue(const QString &val);

private:
    QLineEdit *const mLineEdit;
};
