/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#include "addressbookwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>

using namespace MailMerge;

AddressBookWidget::AddressBookWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
}

AddressBookWidget::~AddressBookWidget()
{
}
