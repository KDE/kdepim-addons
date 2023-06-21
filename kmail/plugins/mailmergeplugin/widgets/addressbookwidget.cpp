/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#include "addressbookwidget.h"
#include <QHBoxLayout>

using namespace MailMerge;

AddressBookWidget::AddressBookWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
}

AddressBookWidget::~AddressBookWidget() = default;

#include "moc_addressbookwidget.cpp"
