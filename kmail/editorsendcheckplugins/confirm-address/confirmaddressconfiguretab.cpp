/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretab.h"

#include "confirmaddressconfiguretabwidget.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>

ConfirmAddressConfigureTab::ConfirmAddressConfigureTab(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

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
    KIdentityManagement::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        auto *w = new ConfirmAddressConfigureTabWidget(this);
        connect(w, &ConfirmAddressConfigureTabWidget::configureChanged, this, &ConfirmAddressConfigureTab::configureChanged);
        mTabWidget->addTab(w, QStringLiteral("%1 (%2)").arg((*it).identityName(), (*it).primaryEmailAddress()));
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}
