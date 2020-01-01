/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    ~ConfirmAddressWidget();

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
