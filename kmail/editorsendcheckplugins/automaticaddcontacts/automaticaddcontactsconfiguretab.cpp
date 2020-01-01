/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "automaticaddcontactsconfiguretab.h"
#include "automaticaddcontactstabwidget.h"

#include <QHBoxLayout>
#include <QTabWidget>
#include <KSharedConfig>
#include <QRegularExpression>
#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>

AutomaticAddContactsConfigureTab::AutomaticAddContactsConfigureTab(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mTabWidget = new QTabWidget(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
    initTab(KIdentityManagement::IdentityManager::self());
}

AutomaticAddContactsConfigureTab::~AutomaticAddContactsConfigureTab()
{
}

void AutomaticAddContactsConfigureTab::initTab(KIdentityManagement::IdentityManager *identityManager)
{
    KIdentityManagement::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        AutomaticAddContactsTabWidget *w = new AutomaticAddContactsTabWidget(this);
        connect(w, &AutomaticAddContactsTabWidget::configureChanged, this, &AutomaticAddContactsConfigureTab::configureChanged);
        mTabWidget->addTab(w, QStringLiteral("%1 (%2)").arg((*it).identityName(), (*it).primaryEmailAddress()));
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}

void AutomaticAddContactsConfigureTab::loadSettings()
{
    for (AutomaticAddContactsTabWidget *w : qAsConst(mListTabWidget)) {
        w->loadSettings();
    }
}

void AutomaticAddContactsConfigureTab::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(QStringLiteral("Automatic Add Contacts \\d+")));
    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (AutomaticAddContactsTabWidget *w : qAsConst(mListTabWidget)) {
        w->saveSettings();
    }
}

void AutomaticAddContactsConfigureTab::resetSettings()
{
    for (AutomaticAddContactsTabWidget *w : qAsConst(mListTabWidget)) {
        w->resetSettings();
    }
}
