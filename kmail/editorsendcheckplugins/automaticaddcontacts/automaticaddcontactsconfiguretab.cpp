/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguretab.h"
#include "automaticaddcontactstabwidget.h"

#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QTabWidget>

AutomaticAddContactsConfigureTab::AutomaticAddContactsConfigureTab(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new QTabWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});
    mTabWidget->setObjectName(QLatin1StringView("tabwidget"));
    mainLayout->addWidget(mTabWidget);
    initTab(KIdentityManagementCore::IdentityManager::self());
}

AutomaticAddContactsConfigureTab::~AutomaticAddContactsConfigureTab() = default;

void AutomaticAddContactsConfigureTab::initTab(KIdentityManagementCore::IdentityManager *identityManager)
{
    KIdentityManagementCore::IdentityManager::ConstIterator end = identityManager->end();
    for (KIdentityManagementCore::IdentityManager::ConstIterator it = identityManager->begin(); it != end; ++it) {
        auto w = new AutomaticAddContactsTabWidget(this);
        connect(w, &AutomaticAddContactsTabWidget::configureChanged, this, &AutomaticAddContactsConfigureTab::configureChanged);
        mTabWidget->addTab(w, QStringLiteral("%1 (%2)").arg((*it).identityName(), (*it).primaryEmailAddress()));
        w->setIdentity((*it).uoid());
        mListTabWidget.append(w);
    }
}

void AutomaticAddContactsConfigureTab::loadSettings()
{
    for (AutomaticAddContactsTabWidget *w : std::as_const(mListTabWidget)) {
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
    for (AutomaticAddContactsTabWidget *w : std::as_const(mListTabWidget)) {
        w->saveSettings();
    }
}

void AutomaticAddContactsConfigureTab::resetSettings()
{
    for (AutomaticAddContactsTabWidget *w : std::as_const(mListTabWidget)) {
        w->resetSettings();
    }
}

#include "moc_automaticaddcontactsconfiguretab.cpp"
