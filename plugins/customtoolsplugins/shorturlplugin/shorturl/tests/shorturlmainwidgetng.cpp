/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "shorturlmainwidgetng.h"
#include "../shorturlwidgetng.h"
#include "../shorturlconfigurewidget.h"

#include <QVBoxLayout>
#include <QPushButton>

ShortUrlMainWidgetNg::ShortUrlMainWidgetNg(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    mConfigWidget = new ShortUrlConfigureWidget;
    lay->addWidget(mConfigWidget);

    QPushButton *saveConfig = new QPushButton(QStringLiteral("Save config"));
    connect(saveConfig, &QPushButton::clicked, this, &ShortUrlMainWidgetNg::slotSaveConfig);
    lay->addWidget(saveConfig);

    mShortUrlWidget = new ShortUrlWidgetNg();
    lay->addWidget(mShortUrlWidget);
    connect(mConfigWidget, &ShortUrlConfigureWidget::settingsChanged, mShortUrlWidget, &ShortUrlWidgetNg::settingsUpdated);
}

void ShortUrlMainWidgetNg::slotSaveConfig()
{
    mConfigWidget->writeConfig();
}
