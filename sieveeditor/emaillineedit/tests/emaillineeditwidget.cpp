/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emaillineeditwidget.h"
#include "../emaillineedit.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QVariant>

EmailLineEditWidget::EmailLineEditWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    EmailLineEdit *mail = new EmailLineEdit(this);
    layout->addWidget(mail);
    layout->addStretch(1);
}
