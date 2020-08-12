/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emaillineeditwidget.h"
#include "../emaillineedit.h"
#include <QVBoxLayout>
#include <QVariant>
#include <QCheckBox>

EmailLineEditWidget::EmailLineEditWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    EmailLineEdit *mail = new EmailLineEdit(this);
    layout->addWidget(mail);
    layout->addStretch(1);
}
