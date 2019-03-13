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

#include "dkimconfiguretab.h"
#include "dkimconfiguretabwidget.h"

#include <KSharedConfig>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QTabWidget>

using namespace MessageViewer;
DKIMConfigureTab::DKIMConfigureTab(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTabWidget = new QTabWidget(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
}

DKIMConfigureTab::~DKIMConfigureTab()
{
}

void DKIMConfigureTab::loadSettings()
{
    for (DKIMConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->loadSettings();
    }
}

void DKIMConfigureTab::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(QStringLiteral("DKIM \\d+")));
    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (DKIMConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->saveSettings();
    }
}

void DKIMConfigureTab::resetSettings()
{
    for (DKIMConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->resetSettings();
    }
}
