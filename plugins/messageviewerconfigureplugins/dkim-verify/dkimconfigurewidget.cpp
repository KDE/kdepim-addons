/*
   Copyright (C) 2018-2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimconfigurewidget.h"
#include "dkimconfiguretab.h"
#include <QWidget>
#include <QVBoxLayout>

#include <KLocalizedString>

using namespace MessageViewer;
DKIMConfigureWidget::DKIMConfigureWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTabWidget = new DKIMConfigureTab(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
}

DKIMConfigureWidget::~DKIMConfigureWidget()
{
}

void DKIMConfigureWidget::loadSettings()
{
    mTabWidget->loadSettings();
}

void DKIMConfigureWidget::saveSettings()
{
    mTabWidget->saveSettings();
}

void DKIMConfigureWidget::resetSettings()
{
    mTabWidget->resetSettings();
}
