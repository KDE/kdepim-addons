/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretab.h"

#include "confirmaddressconfiguretabwidget.h"
#include <KIdentityManagement/Identity>
#include <KIdentityManagement/IdentityManager>
#include <QTabWidget>
#include <QVBoxLayout>

ConfirmAddressConfigureTab::ConfirmAddressConfigureTab(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new QTabWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    initTab(KIdentityManagement::IdentityManager::self());
}

ConfirmAddressConfigureTab::~ConfirmAddressConfigureTab() = default;

void ConfirmAddressConfigureTab::loadSettings(const KConfigGroup &grp)
{
    for (ConfirmAddressConfigureTabWidget *w : std::as_const(mListTabWidget)) {
        w->loadSettings(grp);
    }
}

void ConfirmAddressConfigureTab::saveSettings(KConfigGroup &grp)
{
    for (ConfirmAddressConfigureTabWidget *w : std::as_const(mListTabWidget)) {
        w->saveSettings(grp);
    }
}

void ConfirmAddressConfigureTab::resetSettings()
{
    for (ConfirmAddressConfigureTabWidget *w : std::as_const(mListTabWidget)) {
        w->resetSettings();
    }
}

void ConfirmAddressConfigureTab::initTab(KIdentityManagement::IdentityManager *identityManager)
{
    KIdentityManagement::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagement::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        auto w = new ConfirmAddressConfigureTabWidget(this);
        connect(w, &ConfirmAddressConfigureTabWidget::configureChanged, this, &ConfirmAddressConfigureTab::configureChanged);
        mTabWidget->addTab(w, QStringLiteral("%1 (%2)").arg((*it).identityName(), (*it).primaryEmailAddress()));
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}
