/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidget.h"
#include <QVBoxLayout>

OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(QMargins());
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget()
{
}
