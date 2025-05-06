/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigureaskmanager.h"

#include <KConfigGroup>
#include <QRegularExpression>

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
        info.setText(group.readEntry(QStringLiteral("Text")));
        info.setTitle(group.readEntry(QStringLiteral("Title")));
        info.setEnabled(group.readEntry(QStringLiteral("Enabled"), true));
        infos.append(std::move(info));
    }
    setItems(infos);
}

QStringList AutogenerateConfigureAskManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig();
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(QStringLiteral("AutoGenerate Text #\\d+")));
    return keyGroups;
}

void AutogenerateConfigureAskManager::save()
{
    KSharedConfig::Ptr config;
    const QStringList filterGroups = keyRecorderList(config);

    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = mItems.count(); i < total; ++i) {
        const QString groupName = QStringLiteral("AskIA #%1").arg(i);
        KConfigGroup group = config->group(groupName);
        const AutogenerateConfigureAskInfo &info = mItems.at(i);
        group.writeEntry(QStringLiteral("Text"), info.text());
        group.writeEntry(QStringLiteral("Title"), info.title());
        group.writeEntry(QStringLiteral("Enabled"), info.enabled());
    }
    config->sync();
}

QList<AutogenerateConfigureAskInfo> AutogenerateConfigureAskManager::items() const
{
    return mItems;
}

void AutogenerateConfigureAskManager::setItems(const QList<AutogenerateConfigureAskInfo> &newItems)
{
    if (mItems != newItems) {
        mItems = newItems;
        Q_EMIT changed();
    }
}

#include "moc_autogenerateconfigureaskmanager.cpp"
