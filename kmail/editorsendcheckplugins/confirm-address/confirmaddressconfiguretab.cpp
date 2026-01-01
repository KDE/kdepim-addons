/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretab.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmaddressconfiguretabwidget.h"
#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <QTabWidget>
#include <QVBoxLayout>

ConfirmAddressConfigureTab::ConfirmAddressConfigureTab(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new QTabWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QLatin1StringView("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    initTab(KIdentityManagementCore::IdentityManager::self());
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

void ConfirmAddressConfigureTab::initTab(KIdentityManagementCore::IdentityManager *identityManager)
{
    KIdentityManagementCore::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagementCore::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        auto w = new ConfirmAddressConfigureTabWidget(this);
        connect(w, &ConfirmAddressConfigureTabWidget::configureChanged, this, &ConfirmAddressConfigureTab::configureChanged);
        mTabWidget->addTab(w, u"%1 (%2)"_s.arg((*it).identityName(), (*it).primaryEmailAddress()));
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}

#include "moc_confirmaddressconfiguretab.cpp"
