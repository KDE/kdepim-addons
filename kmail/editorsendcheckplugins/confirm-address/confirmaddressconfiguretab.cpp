/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "confirmaddressconfiguretab.h"
#include "helper_p.h"
#include "confirmaddressconfiguretabwidget.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>

ConfirmAddressConfigureTab::ConfirmAddressConfigureTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mTabWidget = new QTabWidget(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    initTab(KIdentityManagement::IdentityManager::self());
}

ConfirmAddressConfigureTab::~ConfirmAddressConfigureTab()
{

}

void ConfirmAddressConfigureTab::loadSettings(const KConfigGroup &grp)
{
    for (ConfirmAddressConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->loadSettings(grp);
    }
}

void ConfirmAddressConfigureTab::saveSettings(KConfigGroup &grp)
{
    for (ConfirmAddressConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->saveSettings(grp);
    }
}

void ConfirmAddressConfigureTab::resetSettings()
{
    for (ConfirmAddressConfigureTabWidget *w : qAsConst(mListTabWidget)) {
        w->resetSettings();
    }
}

void ConfirmAddressConfigureTab::initTab(KIdentityManagement::IdentityManager *identityManager)
{
    bool needToDeleteIdentity = false;
    if (!identityManager) {
        needToDeleteIdentity = true;
        identityManager = new KIdentityManagement::IdentityManager(true);
    }
    KIdentityManagement::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        ConfirmAddressConfigureTabWidget *w = new ConfirmAddressConfigureTabWidget(this);
        connect(w, &ConfirmAddressConfigureTabWidget::configureChanged, this, &ConfirmAddressConfigureTab::configureChanged);
        mTabWidget->addTab(w, (*it).identityName());
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
    if (needToDeleteIdentity) {
        delete identityManager;
        identityManager = nullptr;
    }
}

