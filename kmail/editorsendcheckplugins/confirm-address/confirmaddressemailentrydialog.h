/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSEMAILENTRYDIALOG_H
#define CONFIRMADDRESSEMAILENTRYDIALOG_H

#include <QDialog>
class QDialogButtonBox;
class QLineEdit;

class ConfirmAddressEmailEntryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmAddressEmailEntryDialog(QWidget *parent = nullptr);
    ~ConfirmAddressEmailEntryDialog() = default;

    Q_REQUIRED_RESULT QString emails() const;
    void setValue(const QString &val);
private:
    QDialogButtonBox *mButtons = nullptr;
    QLineEdit *mLineEdit = nullptr;
};

#endif // CONFIRMADDRESSEMAILENTRYDIALOG_H
