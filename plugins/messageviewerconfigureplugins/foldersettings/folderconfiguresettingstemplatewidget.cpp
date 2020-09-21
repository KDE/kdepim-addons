/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingstemplatewidget.h"
#include <QVBoxLayout>

FolderConfigureSettingsTemplateWidget::FolderConfigureSettingsTemplateWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
}

FolderConfigureSettingsTemplateWidget::~FolderConfigureSettingsTemplateWidget()
{

}
