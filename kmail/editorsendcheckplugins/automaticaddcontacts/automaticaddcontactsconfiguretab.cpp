/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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
#include <KConfigGroup>
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
    mainLayout->setMargin(0);
    mTabWidget = new QTabWidget(this);
    mainLayout->addWidget(mTabWidget);
    initTab();
}

AutomaticAddContactsConfigureTab::~AutomaticAddContactsConfigureTab()
{

}

void AutomaticAddContactsConfigureTab::initTab()
{
    KIdentityManagement::IdentityManager manager(true);
    KIdentityManagement::IdentityManager::ConstIterator end = manager.end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = manager.begin(); it != end; ++it) {
        AutomaticAddContactsTabWidget *w = new AutomaticAddContactsTabWidget(this);
        connect(w, &AutomaticAddContactsTabWidget::configureChanged, this, &AutomaticAddContactsConfigureTab::configureChanged);
        mTabWidget->addTab(w, (*it).identityName());
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}

void AutomaticAddContactsConfigureTab::loadSettings()
{
    Q_FOREACH (AutomaticAddContactsTabWidget *w, mListTabWidget) {
        w->loadSettings();
    }
}

void AutomaticAddContactsConfigureTab::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(QLatin1String("Automatic Add Contacts \\d+")));
    Q_FOREACH (const QString &group, filterGroups) {
        config->deleteGroup(group);
    }
    Q_FOREACH (AutomaticAddContactsTabWidget *w, mListTabWidget) {
        w->saveSettings();
    }
}

void AutomaticAddContactsConfigureTab::resetSettings()
{
    Q_FOREACH (AutomaticAddContactsTabWidget *w, mListTabWidget) {
        w->resetSettings();
    }
}
