/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSWIDGET_H
#define CONFIRMADDRESSWIDGET_H

#include <QWidget>
class QListWidget;
class QListWidgetItem;
class ConfirmAddressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmAddressWidget(QWidget *parent = nullptr);
    ~ConfirmAddressWidget() override;

    void setValidAddresses(const QStringList &addresses);
    void setInvalidAddresses(const QStringList &addresses);
    Q_REQUIRED_RESULT QStringList whiteListSelectedEmails() const;

Q_SIGNALS:
    void updateButtonStatus(bool hasElementChecked);

private:
    void createAddressItems(const QStringList &address, bool valid);
    void slotItemChanged(QListWidgetItem *item);
    QListWidget *mListEmails = nullptr;
};

#endif // CONFIRMADDRESSWIDGET_H
