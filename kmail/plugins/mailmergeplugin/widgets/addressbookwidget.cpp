/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#include "addressbookwidget.h"
#include <QHBoxLayout>

using namespace MailMerge;

AddressBookWidget::AddressBookWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
}

AddressBookWidget::~AddressBookWidget() = default;

#include "moc_addressbookwidget.cpp"
