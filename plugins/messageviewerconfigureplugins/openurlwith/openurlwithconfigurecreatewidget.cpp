/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
    , mServerName(new QLineEdit(this))
    , mCommand(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(QMargins());


    mServerName->setObjectName(QStringLiteral("mServerName"));
    mainLayout->addRow(i18n("Server Name:"), mServerName);

    mCommand->setObjectName(QStringLiteral("mCommand"));
    mainLayout->addRow(i18n("Command:"), mCommand);
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget()
{
}

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateWidget::info() const
{
    OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info;
    info.url = mServerName->text().trimmed();
    info.command = mCommand->text().trimmed();
    return info;
}

void OpenUrlWithConfigureCreateWidget::setInfo(const OpenUrlWithInfo &i)
{
    mServerName->setText(i.url);
    mCommand->setText(i.command);
}

bool OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo::isValid() const
{
    return !url.trimmed().isEmpty() && !command.trimmed().isEmpty();
}
