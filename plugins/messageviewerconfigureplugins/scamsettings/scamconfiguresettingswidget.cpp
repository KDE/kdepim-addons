/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingswidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

ScamConfigureSettingsWidget::ScamConfigureSettingsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
}

ScamConfigureSettingsWidget::~ScamConfigureSettingsWidget()
{
}
