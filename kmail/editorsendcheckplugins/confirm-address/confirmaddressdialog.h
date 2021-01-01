/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSDIALOG_H
#define CONFIRMADDRESSDIALOG_H

#include <QDialog>
class ConfirmAddressWidget;
class ConfirmAddressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmAddressDialog(QWidget *parent = nullptr);
    ~ConfirmAddressDialog() override;

    void setValidAddresses(const QStringList &addresses);
    void setInvalidAddresses(const QStringList &addresses);
    void setCurrentIdentity(uint identity);

Q_SIGNALS:
    void addWhileListEmails(const QStringList &, uint currentIdentity);

private:
    void slotWhiteListSelectedEmails();
    void writeConfig();
    void readConfig();
    uint mCurrentIdentity = 0;
    ConfirmAddressWidget *mConfirmWidget = nullptr;
    QPushButton *mWhiteListEmailsButton = nullptr;
};

#endif // CONFIRMADDRESSDIALOG_H
