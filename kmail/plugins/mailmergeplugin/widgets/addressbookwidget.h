/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include "mailmergeplugin_private_export.h"
#include <QWidget>
namespace MailMerge
{
class MAILMERGEPRIVATE_TESTS_EXPORT AddressBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBookWidget(QWidget *parent = nullptr);
    ~AddressBookWidget() override;
};
}
