/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigureaskmanager.h"

#include <KConfigGroup>
#include <QRegularExpression>
using namespace Qt::Literals::StringLiterals;

AutogenerateConfigureAskManager::AutogenerateConfigureAskManager(QObject *parent)
    : QObject{parent}
{
}

AutogenerateConfigureAskManager::~AutogenerateConfigureAskManager() = default;

void AutogenerateConfigureAskManager::load()
{
    QList<AutogenerateConfigureAskInfo> infos;
    KSharedConfig::Ptr config;
    const QStringList keyGroups = keyRecorderList(config);

    for (const QString &groupName : keyGroups) {
        KConfigGroup group = config->group(groupName);
        AutogenerateConfigureAskInfo info;
        info.setText(group.readEntry(u"Text"_s));
        info.setTitle(group.readEntry(u"Title"_s));
        info.setEnabled(group.readEntry(u"Enabled"_s, true));
        info.setOrder(group.readEntry(u"Order"_s, 0));
        infos.append(std::move(info));
    }
    std::sort(infos.begin(), infos.end(), [&](const auto &firstItem, const auto &secondItem) {
        const int firstOrder = firstItem.order();
        const int secondOrder = secondItem.order();
        if (firstOrder == secondOrder) {
            return firstItem.title() < secondItem.title();
        }
        return firstOrder < secondOrder;
    });
    setInfos(infos);
}

QStringList AutogenerateConfigureAskManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig();
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(u"AskIA #\\d+$"_s));
    return keyGroups;
}

void AutogenerateConfigureAskManager::save()
{
    KSharedConfig::Ptr config;
    const QStringList filterGroups = keyRecorderList(config);

    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = mInfos.count(); i < total; ++i) {
        const QString groupName = u"AskIA #%1"_s.arg(i);
        KConfigGroup group = config->group(groupName);
        const AutogenerateConfigureAskInfo &info = mInfos.at(i);
        group.writeEntry(u"Text"_s, info.text());
        group.writeEntry(u"Title"_s, info.title());
        group.writeEntry(u"Enabled"_s, info.enabled());
        group.writeEntry(u"Order"_s, info.order());
    }
    config->sync();
}

QList<AutogenerateConfigureAskInfo> AutogenerateConfigureAskManager::askInfos() const
{
    return mInfos;
}

void AutogenerateConfigureAskManager::setInfos(const QList<AutogenerateConfigureAskInfo> &newItems)
{
    if (mInfos != newItems) {
        mInfos = newItems;
        Q_EMIT changed();
    }
}

#include "moc_autogenerateconfigureaskmanager.cpp"
