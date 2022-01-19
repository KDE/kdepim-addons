/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
    , mServerName(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(QMargins());

    auto label = new QLabel(i18n("Server Name:"), this);
    mainLayout->addWidget(label);

    mServerName->setObjectName(QStringLiteral("mServerName"));
    mainLayout->addWidget(mServerName);
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget()
{
}

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateWidget::info() const
{
    return {};
}

void OpenUrlWithConfigureCreateWidget::setInfo(const OpenUrlWithInfo &i)
{
    // TODO
}
