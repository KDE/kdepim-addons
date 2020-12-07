/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef ADDRESSBOOKWIDGET_H
#define ADDRESSBOOKWIDGET_H

#include <QWidget>
namespace MailMerge {
class AddressBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBookWidget(QWidget *parent = nullptr);
    ~AddressBookWidget() override;
};
}

#endif // ADDRESSBOOKWIDGET_H
