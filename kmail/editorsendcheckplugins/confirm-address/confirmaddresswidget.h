/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    [[nodiscard]] QStringList whiteListSelectedEmails() const;

Q_SIGNALS:
    void updateButtonStatus(bool hasElementChecked);

private:
    void createAddressItems(const QStringList &address, bool valid);
    void slotItemChanged(QListWidgetItem *item);
    QListWidget *const mListEmails;
};
