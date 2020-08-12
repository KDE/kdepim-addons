/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#include "addressbookwidget.h"
#include <QHBoxLayout>

using namespace MailMerge;

AddressBookWidget::AddressBookWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout;
    setLayout(hbox);
}

AddressBookWidget::~AddressBookWidget()
{
}
